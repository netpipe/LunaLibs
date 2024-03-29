/* FluidSynth - A Software Synthesizer
 *
 * Copyright (C) 2003  Peter Hanappe and others.
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public License
 * as published by the Free Software Foundation; either version 2.1 of
 * the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free
 * Software Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA
 * 02110-1301, USA
 */

#include "fluid_rvoice_mixer.h"
#include "fluid_rvoice.h"
#include "fluid_sys.h"
#include "fluid_rev.h"
#include "fluid_chorus.h"
#include "fluidsynth_priv.h"
#include "fluid_ladspa.h"
#include "fluid_synth.h"


#define ENABLE_MIXER_THREADS 1

// If less than x voices, the thread overhead is larger than the gain,
// so don't activate the thread(s).
#define VOICES_PER_THREAD 8

typedef struct _fluid_mixer_buffers_t fluid_mixer_buffers_t;

struct _fluid_mixer_buffers_t {
  fluid_rvoice_mixer_t* mixer; /**< Owner of object */
#if ENABLE_MIXER_THREADS
  fluid_thread_t* thread;     /**< Thread object */
#endif

  fluid_rvoice_t** finished_voices; /* List of voices who have finished */
  int finished_voice_count;

  fluid_atomic_int_t ready;             /**< Atomic: buffers are ready for mixing */
  
  int buf_count;
  fluid_real_t** left_buf;
  fluid_real_t** right_buf;

  int fx_buf_count;
  fluid_real_t** fx_left_buf;
  fluid_real_t** fx_right_buf;
};

typedef struct _fluid_mixer_fx_t fluid_mixer_fx_t;

struct _fluid_mixer_fx_t {
  fluid_revmodel_t* reverb; /**< Reverb unit */
  fluid_chorus_t* chorus; /**< Chorus unit */
  int with_reverb;        /**< Should the synth use the built-in reverb unit? */
  int with_chorus;        /**< Should the synth use the built-in chorus unit? */
  int mix_fx_to_out;      /**< Should the effects be mixed in with the primary output? */
};

struct _fluid_rvoice_mixer_t {
  fluid_mixer_fx_t fx;

  fluid_mixer_buffers_t buffers; /**< Used by mixer only: own buffers */
  fluid_rvoice_eventhandler_t* eventhandler;

  fluid_rvoice_t** rvoices; /**< Read-only: Voices array, sorted so that all nulls are last */
  int polyphony; /**< Read-only: Length of voices array */
  int active_voices; /**< Read-only: Number of non-null voices */
  int current_blockcount;      /**< Read-only: how many blocks to process this time */

#ifdef LADSPA
  fluid_ladspa_fx_t* ladspa_fx; /**< Used by mixer only: Effects unit for LADSPA support. Never created or freed */
#endif

#if ENABLE_MIXER_THREADS
//  int sleeping_threads;        /**< Atomic: number of threads currently asleep */
//  int active_threads;          /**< Atomic: number of threads in the thread loop */
  fluid_atomic_int_t threads_should_terminate; /**< Atomic: Set to TRUE when threads should terminate */
  fluid_atomic_int_t current_rvoice;           /**< Atomic: for the threads to know next voice to  */
  fluid_cond_t* wakeup_threads; /**< Signalled when the threads should wake up */
  fluid_cond_mutex_t* wakeup_threads_m; /**< wakeup_threads mutex companion */
  fluid_cond_t* thread_ready; /**< Signalled from thread, when the thread has a buffer ready for mixing */
  fluid_cond_mutex_t* thread_ready_m; /**< thread_ready mutex companion */

  int thread_count;            /**< Number of extra mixer threads for multi-core rendering */
  fluid_mixer_buffers_t* threads;    /**< Array of mixer threads (thread_count in length) */
#endif
};

#if ENABLE_MIXER_THREADS
static void delete_rvoice_mixer_threads(fluid_rvoice_mixer_t* mixer);
#endif

static FLUID_INLINE void 
fluid_rvoice_mixer_process_fx(fluid_rvoice_mixer_t* mixer)
{
  int i;
  fluid_profile_ref_var(prof_ref);
  if (mixer->fx.with_reverb) {
    if (mixer->fx.mix_fx_to_out) {
      for (i=0; i < mixer->current_blockcount * FLUID_BUFSIZE; i += FLUID_BUFSIZE)
        fluid_revmodel_processmix(mixer->fx.reverb, 
                                  &mixer->buffers.fx_left_buf[SYNTH_REVERB_CHANNEL][i],
				  &mixer->buffers.left_buf[0][i],
				  &mixer->buffers.right_buf[0][i]);
    } 
    else {
      for (i=0; i < mixer->current_blockcount * FLUID_BUFSIZE; i += FLUID_BUFSIZE)
        fluid_revmodel_processreplace(mixer->fx.reverb, 
                                  &mixer->buffers.fx_left_buf[SYNTH_REVERB_CHANNEL][i],
				  &mixer->buffers.fx_left_buf[SYNTH_REVERB_CHANNEL][i],
				  &mixer->buffers.fx_right_buf[SYNTH_REVERB_CHANNEL][i]);
    }
    fluid_profile(FLUID_PROF_ONE_BLOCK_REVERB, prof_ref,0,
	              mixer->current_blockcount * FLUID_BUFSIZE);
  }
  
  if (mixer->fx.with_chorus) {
    if (mixer->fx.mix_fx_to_out) {
      for (i=0; i < mixer->current_blockcount * FLUID_BUFSIZE; i += FLUID_BUFSIZE)
        fluid_chorus_processmix(mixer->fx.chorus, 
                                &mixer->buffers.fx_left_buf[SYNTH_CHORUS_CHANNEL][i],
			        &mixer->buffers.left_buf[0][i],
				&mixer->buffers.right_buf[0][i]);
    } 
    else {
      for (i=0; i < mixer->current_blockcount * FLUID_BUFSIZE; i += FLUID_BUFSIZE)
        fluid_chorus_processreplace(mixer->fx.chorus, 
                                &mixer->buffers.fx_left_buf[SYNTH_CHORUS_CHANNEL][i],
				&mixer->buffers.fx_left_buf[SYNTH_CHORUS_CHANNEL][i],
				&mixer->buffers.fx_right_buf[SYNTH_CHORUS_CHANNEL][i]);
    }
    fluid_profile(FLUID_PROF_ONE_BLOCK_CHORUS, prof_ref,0,
	              mixer->current_blockcount * FLUID_BUFSIZE);
  }
  
#ifdef LADSPA
  /* Run the signal through the LADSPA Fx unit. The buffers have already been
   * set up in fluid_rvoice_mixer_set_ladspa. */
  if (mixer->ladspa_fx) {
      fluid_ladspa_run(mixer->ladspa_fx, mixer->current_blockcount, FLUID_BUFSIZE);
      fluid_check_fpe("LADSPA");
  }
#endif
}

/**
 * Glue to get fluid_rvoice_buffers_mix what it wants
 * Note: Make sure outbufs has 2 * (buf_count + fx_buf_count) elements before calling
 */
static FLUID_INLINE int 
fluid_mixer_buffers_prepare(fluid_mixer_buffers_t* buffers, fluid_real_t** outbufs)
{
  fluid_real_t *reverb_buf, *chorus_buf;
  int i;
  int with_reverb = buffers->mixer->fx.with_reverb;
  int with_chorus = buffers->mixer->fx.with_chorus;

  /* Set up the reverb and chorus buffers only when the effect is enabled or
   * when LADSPA is active. Nonexisting buffers are detected in the DSP loop.
   * Not sending the effect signals saves some time in that case. */
#ifdef LADSPA
  int with_ladspa = (buffers->mixer->ladspa_fx != NULL);
  with_reverb = (with_reverb | with_ladspa);
  with_chorus = (with_chorus | with_ladspa);
#endif
  reverb_buf = (with_reverb) ? buffers->fx_left_buf[SYNTH_REVERB_CHANNEL] : NULL;
  chorus_buf = (with_chorus) ? buffers->fx_left_buf[SYNTH_CHORUS_CHANNEL] : NULL;
  outbufs[buffers->buf_count*2 + SYNTH_REVERB_CHANNEL] = reverb_buf;
  outbufs[buffers->buf_count*2 + SYNTH_CHORUS_CHANNEL] = chorus_buf;

      /* The output associated with a MIDI channel is wrapped around
       * using the number of audio groups as modulo divider.  This is
       * typically the number of output channels on the 'sound card',
       * as long as the LADSPA Fx unit is not used. In case of LADSPA
       * unit, think of it as subgroups on a mixer.
       *
       * For example: Assume that the number of groups is set to 2.
       * Then MIDI channel 1, 3, 5, 7 etc. go to output 1, channels 2,
       * 4, 6, 8 etc to output 2.  Or assume 3 groups: Then MIDI
       * channels 1, 4, 7, 10 etc go to output 1; 2, 5, 8, 11 etc to
       * output 2, 3, 6, 9, 12 etc to output 3.
       */

  for (i = 0; i < buffers->buf_count; i++) {
    outbufs[i*2] = buffers->left_buf[i];
    outbufs[i*2+1] = buffers->right_buf[i];
  }
  return buffers->buf_count*2 + 2;
}


static FLUID_INLINE void
fluid_finish_rvoice(fluid_mixer_buffers_t* buffers, fluid_rvoice_t* rvoice)
{
  if (buffers->finished_voice_count < buffers->mixer->polyphony)
    buffers->finished_voices[buffers->finished_voice_count++] = rvoice;
  else
    FLUID_LOG(FLUID_ERR, "Exceeded finished voices array, try increasing polyphony");
}

static void   
fluid_mixer_buffer_process_finished_voices(fluid_mixer_buffers_t* buffers)
{
  int i,j;
  for (i=0; i < buffers->finished_voice_count; i++) {
    fluid_rvoice_t* v = buffers->finished_voices[i];
    int av = buffers->mixer->active_voices; 
    for (j=0; j < av; j++) {
      if (v == buffers->mixer->rvoices[j]) {
        av--;
        /* Pack the array */
        if (j < av) 
          buffers->mixer->rvoices[j] = buffers->mixer->rvoices[av];
      }
    }
    buffers->mixer->active_voices = av;
    
    fluid_rvoice_eventhandler_finished_voice_callback(buffers->mixer->eventhandler, v);
  }
  buffers->finished_voice_count = 0;
}

static FLUID_INLINE void fluid_rvoice_mixer_process_finished_voices(fluid_rvoice_mixer_t* mixer)
{
#if ENABLE_MIXER_THREADS  
  int i;
  for (i=0; i < mixer->thread_count; i++)
    fluid_mixer_buffer_process_finished_voices(&mixer->threads[i]);
#endif
  fluid_mixer_buffer_process_finished_voices(&mixer->buffers);
}


static FLUID_INLINE fluid_real_t* 
get_dest_buf(fluid_rvoice_buffers_t* buffers, int index,
             fluid_real_t** dest_bufs, int dest_bufcount)
{
  int j = buffers->bufs[index].mapping;
  if (j >= dest_bufcount || j < 0) return NULL;
  return dest_bufs[j];
}

/**
 * Mix data down to buffers
 *
 * @param buffers Destination buffer(s)
 * @param dsp_buf Mono sample source
 * @param samplecount Number of samples to process (no FLUID_BUFSIZE restriction)
 * @param dest_bufs Array of buffers to mixdown to
 * @param dest_bufcount Length of dest_bufs
 */
static void 
fluid_rvoice_buffers_mix(fluid_rvoice_buffers_t* buffers, 
                         fluid_real_t* dsp_buf, int start, int samplecount, 
                         fluid_real_t** dest_bufs, int dest_bufcount)
{
  int bufcount = buffers->count;
  int i, dsp_i;
  if (!samplecount || !bufcount || !dest_bufcount) 
    return;

  for (i=0; i < bufcount; i++) {
    fluid_real_t* buf = get_dest_buf(buffers, i, dest_bufs, dest_bufcount);
    fluid_real_t* next_buf;
    fluid_real_t amp = buffers->bufs[i].amp;
    if (buf == NULL || amp == 0.0f)
      continue;

    /* Optimization for centered stereo samples - we can save one 
       multiplication per sample */
    next_buf = (i+1 >= bufcount ? NULL : get_dest_buf(buffers, i+1, dest_bufs, dest_bufcount));
    if (next_buf && buffers->bufs[i+1].amp == amp) {
      for (dsp_i = start; dsp_i < samplecount; dsp_i++) {
        fluid_real_t samp = amp * dsp_buf[dsp_i]; 
        buf[dsp_i] += samp;
        next_buf[dsp_i] += samp;
      }
      i++;
    }
    else {
      for (dsp_i = start; dsp_i < samplecount; dsp_i++)
        buf[dsp_i] += amp * dsp_buf[dsp_i];
    }
  }
}

/**
 * Synthesize one voice and add to buffer.
 * NOTE: If return value is less than blockcount*FLUID_BUFSIZE, that means 
 * voice has been finished, removed and possibly replaced with another voice.
 */
static FLUID_INLINE void
fluid_mixer_buffers_render_one(fluid_mixer_buffers_t* buffers, 
			       fluid_rvoice_t* rvoice, fluid_real_t** dest_bufs, 
			       unsigned int dest_bufcount)
{
  int blockcount = buffers->mixer->current_blockcount;
  int i, result = 0, start = 0;

  FLUID_DECLARE_VLA(fluid_real_t, local_buf, FLUID_BUFSIZE*blockcount);

  for (i=0; i < blockcount; i++) {
    int s = fluid_rvoice_write(rvoice, &local_buf[FLUID_BUFSIZE*i]);
    if (s == -1) {
      start += FLUID_BUFSIZE;
      s = FLUID_BUFSIZE;
    }
    result += s;
    if (s < FLUID_BUFSIZE) {
      break;
    }
  }
  fluid_rvoice_buffers_mix(&rvoice->buffers, local_buf, start, result-start, dest_bufs, dest_bufcount);

  if (result < buffers->mixer->current_blockcount * FLUID_BUFSIZE) {
    fluid_finish_rvoice(buffers, rvoice);
  }
}

DECLARE_FLUID_RVOICE_FUNCTION(fluid_rvoice_mixer_add_voice)
{
  int i;
  fluid_rvoice_mixer_t* mixer = obj;
  fluid_rvoice_t* voice = param[0].ptr;

  if (mixer->active_voices < mixer->polyphony) {
    mixer->rvoices[mixer->active_voices++] = voice;
    return; // success
  }
  
  /* See if any voices just finished, if so, take its place.
     This can happen in voice overflow conditions. */
  for (i=0; i < mixer->active_voices; i++) {
    if (mixer->rvoices[i] == voice) {
      FLUID_LOG(FLUID_ERR, "Internal error: Trying to replace an existing rvoice in fluid_rvoice_mixer_add_voice?!");
      return;
    }
    if (mixer->rvoices[i]->envlfo.volenv.section == FLUID_VOICE_ENVFINISHED) {
      fluid_finish_rvoice(&mixer->buffers, mixer->rvoices[i]);
      mixer->rvoices[i] = voice;
      return; // success
    }
  }

  /* This should never happen */
  FLUID_LOG(FLUID_ERR, "Trying to exceed polyphony in fluid_rvoice_mixer_add_voice");
  return;
}

static int 
fluid_mixer_buffers_update_polyphony(fluid_mixer_buffers_t* buffers, int value)
{
  void* newptr;

  if (buffers->finished_voice_count > value) 
    return FLUID_FAILED;
  
  newptr = FLUID_REALLOC(buffers->finished_voices, value * sizeof(fluid_rvoice_t*));
  if (newptr == NULL && value > 0) 
    return FLUID_FAILED;
  buffers->finished_voices = newptr;  
  return FLUID_OK;
}

/**
 * Update polyphony - max number of voices (NOTE: not hard real-time capable)
 * @return FLUID_OK or FLUID_FAILED
 */
DECLARE_FLUID_RVOICE_FUNCTION(fluid_rvoice_mixer_set_polyphony)
{
  void* newptr;
  fluid_rvoice_mixer_t* handler = obj;
  int value = param[0].i;
  
  if (handler->active_voices > value) 
    return /*FLUID_FAILED*/;

  newptr = FLUID_REALLOC(handler->rvoices, value * sizeof(fluid_rvoice_t*));
  if (newptr == NULL) 
    return /*FLUID_FAILED*/;
  handler->rvoices = newptr;

  if (fluid_mixer_buffers_update_polyphony(&handler->buffers, value) 
      == FLUID_FAILED)
    return /*FLUID_FAILED*/;

#if ENABLE_MIXER_THREADS
  {
    int i;
    for (i=0; i < handler->thread_count; i++)
      if (fluid_mixer_buffers_update_polyphony(&handler->threads[i], value) 
          == FLUID_FAILED)
        return /*FLUID_FAILED*/;
  }
#endif

  handler->polyphony = value;
  return /*FLUID_OK*/;
}


static void 
fluid_render_loop_singlethread(fluid_rvoice_mixer_t* mixer)
{
  int i;
  FLUID_DECLARE_VLA(fluid_real_t*, bufs, 
		    mixer->buffers.buf_count * 2 + mixer->buffers.fx_buf_count * 2);
  int bufcount = fluid_mixer_buffers_prepare(&mixer->buffers, bufs);
  fluid_profile_ref_var(prof_ref);
  for (i=0; i < mixer->active_voices; i++) {
    fluid_mixer_buffers_render_one(&mixer->buffers, mixer->rvoices[i], bufs, 
				   bufcount);
    fluid_profile(FLUID_PROF_ONE_BLOCK_VOICE, prof_ref,1,
	              mixer->current_blockcount * FLUID_BUFSIZE);
  }
}


static FLUID_INLINE void
fluid_mixer_buffers_zero(fluid_mixer_buffers_t* buffers)
{
  int i;
  int size = buffers->mixer->current_blockcount * FLUID_BUFSIZE * sizeof(fluid_real_t);
  /* TODO: Optimize by only zero out the buffers we actually use later on. */
  for (i=0; i < buffers->buf_count; i++) {
    FLUID_MEMSET(buffers->left_buf[i], 0, size);
    FLUID_MEMSET(buffers->right_buf[i], 0, size);
  }
  for (i=0; i < buffers->fx_buf_count; i++) {
    FLUID_MEMSET(buffers->fx_left_buf[i], 0, size);
    FLUID_MEMSET(buffers->fx_right_buf[i], 0, size);
  }
}



static int 
fluid_mixer_buffers_init(fluid_mixer_buffers_t* buffers, fluid_rvoice_mixer_t* mixer)
{
  int i, samplecount;
  
  buffers->mixer = mixer;
  buffers->buf_count = buffers->mixer->buffers.buf_count;
  buffers->fx_buf_count = buffers->mixer->buffers.fx_buf_count;
  samplecount = FLUID_BUFSIZE * FLUID_MIXER_MAX_BUFFERS_DEFAULT;
  
 
  /* Left and right audio buffers */

  buffers->left_buf = FLUID_ARRAY(fluid_real_t*, buffers->buf_count);
  buffers->right_buf = FLUID_ARRAY(fluid_real_t*, buffers->buf_count);

  if ((buffers->left_buf == NULL) || (buffers->right_buf == NULL)) {
    FLUID_LOG(FLUID_ERR, "Out of memory");
    return 0;
  }

  FLUID_MEMSET(buffers->left_buf, 0, buffers->buf_count * sizeof(fluid_real_t*));
  FLUID_MEMSET(buffers->right_buf, 0, buffers->buf_count * sizeof(fluid_real_t*));

  for (i = 0; i < buffers->buf_count; i++) {

    buffers->left_buf[i] = FLUID_ARRAY(fluid_real_t, samplecount);
    buffers->right_buf[i] = FLUID_ARRAY(fluid_real_t, samplecount);

    if ((buffers->left_buf[i] == NULL) || (buffers->right_buf[i] == NULL)) {
      FLUID_LOG(FLUID_ERR, "Out of memory");
      return 0;
    }
  }

  /* Effects audio buffers */

  buffers->fx_left_buf = FLUID_ARRAY(fluid_real_t*, buffers->fx_buf_count);
  buffers->fx_right_buf = FLUID_ARRAY(fluid_real_t*, buffers->fx_buf_count);

  if ((buffers->fx_left_buf == NULL) || (buffers->fx_right_buf == NULL)) {
    FLUID_LOG(FLUID_ERR, "Out of memory");
    return 0;
  }

  FLUID_MEMSET(buffers->fx_left_buf, 0, buffers->fx_buf_count * sizeof(fluid_real_t*));
  FLUID_MEMSET(buffers->fx_right_buf, 0, buffers->fx_buf_count * sizeof(fluid_real_t*));

  for (i = 0; i < buffers->fx_buf_count; i++) {
    buffers->fx_left_buf[i] = FLUID_ARRAY(fluid_real_t, samplecount);
    buffers->fx_right_buf[i] = FLUID_ARRAY(fluid_real_t, samplecount);

    if ((buffers->fx_left_buf[i] == NULL) || (buffers->fx_right_buf[i] == NULL)) {
      FLUID_LOG(FLUID_ERR, "Out of memory");
      return 0;
    }
  }
  
  buffers->finished_voices = NULL;
  if (fluid_mixer_buffers_update_polyphony(buffers, mixer->polyphony) 
      == FLUID_FAILED) {
    FLUID_LOG(FLUID_ERR, "Out of memory");
    return 0;
  }
  
  return 1;
}

/**
 * Note: Not hard real-time capable (calls malloc)
 */
DECLARE_FLUID_RVOICE_FUNCTION(fluid_rvoice_mixer_set_samplerate)
{
  fluid_rvoice_mixer_t* mixer = obj;
  fluid_real_t samplerate = param[1].real; // becausee fluid_synth_update_mixer() puts real into arg2
  
  if (mixer->fx.chorus)
    delete_fluid_chorus(mixer->fx.chorus);
  
  mixer->fx.chorus = new_fluid_chorus(samplerate);
  if (mixer->fx.reverb)
	  fluid_revmodel_samplerate_change(mixer->fx.reverb, samplerate);
  
#if LADSPA
  if (mixer->ladspa_fx != NULL)
  {
    fluid_ladspa_set_sample_rate(mixer->ladspa_fx, samplerate);
  }
#endif
}


/**
 * @param buf_count number of primary stereo buffers
 * @param fx_buf_count number of stereo effect buffers
 */
fluid_rvoice_mixer_t* 
new_fluid_rvoice_mixer(int buf_count, int fx_buf_count, fluid_real_t sample_rate, fluid_rvoice_eventhandler_t* evthandler)
{
  fluid_rvoice_mixer_t* mixer = FLUID_NEW(fluid_rvoice_mixer_t);
  if (mixer == NULL) {
    FLUID_LOG(FLUID_ERR, "Out of memory");
    return NULL;
  }
  FLUID_MEMSET(mixer, 0, sizeof(fluid_rvoice_mixer_t));
  mixer->eventhandler = evthandler;
  mixer->buffers.buf_count = buf_count;
  mixer->buffers.fx_buf_count = fx_buf_count;
  
  /* allocate the reverb module */
  mixer->fx.reverb = new_fluid_revmodel(sample_rate);
  mixer->fx.chorus = new_fluid_chorus(sample_rate);
  if (mixer->fx.reverb == NULL || mixer->fx.chorus == NULL) {
    FLUID_LOG(FLUID_ERR, "Out of memory");
    delete_fluid_rvoice_mixer(mixer);
    return NULL;
  }
  
  if (!fluid_mixer_buffers_init(&mixer->buffers, mixer)) {
    delete_fluid_rvoice_mixer(mixer);
    return NULL;
  }
  
#if ENABLE_MIXER_THREADS
  mixer->thread_ready = new_fluid_cond();
  mixer->wakeup_threads = new_fluid_cond();
  mixer->thread_ready_m = new_fluid_cond_mutex();
  mixer->wakeup_threads_m = new_fluid_cond_mutex();
  if (!mixer->thread_ready || !mixer->wakeup_threads || 
      !mixer->thread_ready_m || !mixer->wakeup_threads_m) {
    delete_fluid_rvoice_mixer(mixer);
    return NULL;
  }
#endif
  
  return mixer;
}

static void
fluid_mixer_buffers_free(fluid_mixer_buffers_t* buffers)
{
  int i;
  
  FLUID_FREE(buffers->finished_voices);
  
  /* free all the sample buffers */
  if (buffers->left_buf != NULL) {
    for (i = 0; i < buffers->buf_count; i++) {
      if (buffers->left_buf[i] != NULL) {
	FLUID_FREE(buffers->left_buf[i]);
      }
    }
    FLUID_FREE(buffers->left_buf);
  }

  if (buffers->right_buf != NULL) {
    for (i = 0; i < buffers->buf_count; i++) {
      if (buffers->right_buf[i] != NULL) {
	FLUID_FREE(buffers->right_buf[i]);
      }
    }
    FLUID_FREE(buffers->right_buf);
  }

  if (buffers->fx_left_buf != NULL) {
    for (i = 0; i < buffers->fx_buf_count; i++) {
      if (buffers->fx_left_buf[i] != NULL) {
	FLUID_FREE(buffers->fx_left_buf[i]);
      }
    }
    FLUID_FREE(buffers->fx_left_buf);
  }

  if (buffers->fx_right_buf != NULL) {
    for (i = 0; i < buffers->fx_buf_count; i++) {
      if (buffers->fx_right_buf[i] != NULL) {
	FLUID_FREE(buffers->fx_right_buf[i]);
      }
    }
    FLUID_FREE(buffers->fx_right_buf);
  }  
}

void delete_fluid_rvoice_mixer(fluid_rvoice_mixer_t* mixer)
{
  fluid_return_if_fail(mixer != NULL);
  
#if ENABLE_MIXER_THREADS
  delete_rvoice_mixer_threads(mixer);
  
  if (mixer->thread_ready)
    delete_fluid_cond(mixer->thread_ready);
  if (mixer->wakeup_threads)
    delete_fluid_cond(mixer->wakeup_threads);
  if (mixer->thread_ready_m)
    delete_fluid_cond_mutex(mixer->thread_ready_m);
  if (mixer->wakeup_threads_m)
    delete_fluid_cond_mutex(mixer->wakeup_threads_m);
#endif
  fluid_mixer_buffers_free(&mixer->buffers);
  if (mixer->fx.reverb)
    delete_fluid_revmodel(mixer->fx.reverb);
  if (mixer->fx.chorus)
    delete_fluid_chorus(mixer->fx.chorus);
  FLUID_FREE(mixer->rvoices);
  FLUID_FREE(mixer);
}


#ifdef LADSPA				    
/**
 * Set a LADSPS fx instance to be used by the mixer and assign the mixer buffers
 * as LADSPA host buffers with sensible names */
void fluid_rvoice_mixer_set_ladspa(fluid_rvoice_mixer_t* mixer,
        fluid_ladspa_fx_t *ladspa_fx, int audio_groups)
{
    mixer->ladspa_fx = ladspa_fx;
    if (ladspa_fx == NULL)
    {
        return;
    }

    fluid_ladspa_add_host_ports(ladspa_fx, "Main:L", audio_groups,
            mixer->buffers.left_buf);

    fluid_ladspa_add_host_ports(ladspa_fx, "Main:R", audio_groups,
            mixer->buffers.right_buf);

    fluid_ladspa_add_host_ports(ladspa_fx, "Reverb:Send", 1,
            &mixer->buffers.fx_left_buf[SYNTH_REVERB_CHANNEL]);

    fluid_ladspa_add_host_ports(ladspa_fx, "Chorus:Send", 1,
            &mixer->buffers.fx_left_buf[SYNTH_CHORUS_CHANNEL]);
}
#endif

DECLARE_FLUID_RVOICE_FUNCTION(fluid_rvoice_mixer_set_reverb_enabled)
{
  fluid_rvoice_mixer_t* mixer = obj;
  int on = param[0].i;
  
  mixer->fx.with_reverb = on;
}

DECLARE_FLUID_RVOICE_FUNCTION(fluid_rvoice_mixer_set_chorus_enabled)
{
  fluid_rvoice_mixer_t* mixer = obj;
  int on = param[0].i;
  mixer->fx.with_chorus = on;
}

void fluid_rvoice_mixer_set_mix_fx(fluid_rvoice_mixer_t* mixer, int on)
{
  mixer->fx.mix_fx_to_out = on;
}

DECLARE_FLUID_RVOICE_FUNCTION(fluid_rvoice_mixer_set_chorus_params)
{
  fluid_rvoice_mixer_t* mixer = obj;
  int set = param[0].i;
  int nr = param[1].i;
  fluid_real_t level = param[2].real;
  fluid_real_t speed = param[3].real;
  fluid_real_t depth_ms = param[4].real;
  int type = param[5].i;
  
  fluid_chorus_set(mixer->fx.chorus, set, nr, level, speed, depth_ms, type);
}

DECLARE_FLUID_RVOICE_FUNCTION(fluid_rvoice_mixer_set_reverb_params)
{
    fluid_rvoice_mixer_t* mixer = obj;
    int set = param[0].i;
    fluid_real_t roomsize = param[1].real;
    fluid_real_t damping = param[2].real;
    fluid_real_t width = param[3].real;
    fluid_real_t level = param[4].real;
    
  fluid_revmodel_set(mixer->fx.reverb, set, roomsize, damping, width, level); 
}

DECLARE_FLUID_RVOICE_FUNCTION(fluid_rvoice_mixer_reset_reverb)
{
  fluid_rvoice_mixer_t* mixer = obj;
  fluid_revmodel_reset(mixer->fx.reverb);
}

DECLARE_FLUID_RVOICE_FUNCTION(fluid_rvoice_mixer_reset_chorus)
{
  fluid_rvoice_mixer_t* mixer = obj;
  fluid_chorus_reset(mixer->fx.chorus);
}

int fluid_rvoice_mixer_get_bufs(fluid_rvoice_mixer_t* mixer, 
				  fluid_real_t*** left, fluid_real_t*** right)
{
  *left = mixer->buffers.left_buf;
  *right = mixer->buffers.right_buf;
  return mixer->buffers.buf_count;
}

int fluid_rvoice_mixer_get_fx_bufs(fluid_rvoice_mixer_t* mixer, 
                  fluid_real_t*** fx_left, fluid_real_t*** fx_right)
{
  *fx_left = mixer->buffers.fx_left_buf;
  *fx_right = mixer->buffers.fx_right_buf;
  return mixer->buffers.fx_buf_count;
}

int fluid_rvoice_mixer_get_bufcount(fluid_rvoice_mixer_t* mixer)
{
    return FLUID_MIXER_MAX_BUFFERS_DEFAULT;
}

#if WITH_PROFILING
int fluid_rvoice_mixer_get_active_voices(fluid_rvoice_mixer_t* mixer)
{
	return mixer->active_voices;
}
#endif

#if ENABLE_MIXER_THREADS

static FLUID_INLINE fluid_rvoice_t* 
fluid_mixer_get_mt_rvoice(fluid_rvoice_mixer_t* mixer)
{
  int i = fluid_atomic_int_exchange_and_add(&mixer->current_rvoice, 1);
  if (i >= mixer->active_voices) 
    return NULL;
  return mixer->rvoices[i];
}

#define THREAD_BUF_PROCESSING 0
#define THREAD_BUF_VALID 1
#define THREAD_BUF_NODATA 2
#define THREAD_BUF_TERMINATE 3

/* Core thread function (processes voices in parallel to primary synthesis thread) */
static fluid_thread_return_t
fluid_mixer_thread_func (void* data)
{
  fluid_mixer_buffers_t* buffers = data;  
  fluid_rvoice_mixer_t* mixer = buffers->mixer;
  int hasValidData = 0;
  FLUID_DECLARE_VLA(fluid_real_t*, bufs, buffers->buf_count*2 + buffers->fx_buf_count*2);
  int bufcount = 0;
  
  while (!fluid_atomic_int_get(&mixer->threads_should_terminate)) {
    fluid_rvoice_t* rvoice = fluid_mixer_get_mt_rvoice(mixer);
    if (rvoice == NULL) {
      // if no voices: signal rendered buffers, sleep
      fluid_atomic_int_set(&buffers->ready, hasValidData ? THREAD_BUF_VALID : THREAD_BUF_NODATA);
      fluid_cond_mutex_lock(mixer->thread_ready_m);
      fluid_cond_signal(mixer->thread_ready);
      fluid_cond_mutex_unlock(mixer->thread_ready_m);
      
      fluid_cond_mutex_lock(mixer->wakeup_threads_m);
      while (1) {
        int j = fluid_atomic_int_get(&buffers->ready); 
        if (j == THREAD_BUF_PROCESSING || j == THREAD_BUF_TERMINATE)
          break;
        fluid_cond_wait(mixer->wakeup_threads, mixer->wakeup_threads_m);
      }
      fluid_cond_mutex_unlock(mixer->wakeup_threads_m);
      
      hasValidData = 0;
    }
    else {
      // else: if buffer is not zeroed, zero buffers
      if (!hasValidData) {
        fluid_mixer_buffers_zero(buffers);
	bufcount = fluid_mixer_buffers_prepare(buffers, bufs);
	hasValidData = 1;
      }
      // then render voice to buffers
      fluid_mixer_buffers_render_one(buffers, rvoice, bufs, bufcount);
    }
  }

  return FLUID_THREAD_RETURN_VALUE;
}

static void
fluid_mixer_buffers_mix(fluid_mixer_buffers_t* dest, fluid_mixer_buffers_t* src)
{
  int i,j;
  int scount = dest->mixer->current_blockcount * FLUID_BUFSIZE;
  int minbuf;
  
  minbuf = dest->buf_count;
  if (minbuf > src->buf_count)
    minbuf = src->buf_count;
  for (i=0; i < minbuf; i++) {
    for (j=0; j < scount; j++) {
      dest->left_buf[i][j] += src->left_buf[i][j];
      dest->right_buf[i][j] += src->right_buf[i][j];
    }
  }

  minbuf = dest->fx_buf_count;
  if (minbuf > src->fx_buf_count)
    minbuf = src->fx_buf_count;
  for (i=0; i < minbuf; i++) {
    for (j=0; j < scount; j++) {
      dest->fx_left_buf[i][j] += src->fx_left_buf[i][j];
      dest->fx_right_buf[i][j] += src->fx_right_buf[i][j];
    }
  }
}


/**
 * Go through all threads and see if someone is finished for mixing 
 */
static FLUID_INLINE int
fluid_mixer_mix_in(fluid_rvoice_mixer_t* mixer, int extra_threads)
{
  int i, result, hasmixed;
  do {
    hasmixed = 0;
    result = 0;
    for (i=0; i < extra_threads; i++) {
      int j = fluid_atomic_int_get(&mixer->threads[i].ready);
      switch (j) {
	case THREAD_BUF_PROCESSING: 
	  result = 1;
	  break;
	case THREAD_BUF_VALID:
          fluid_atomic_int_set(&mixer->threads[i].ready, THREAD_BUF_NODATA);
	  fluid_mixer_buffers_mix(&mixer->buffers, &mixer->threads[i]);
	  hasmixed = 1;
	  break;
      }
    }
  } while (hasmixed);
  return result;
}

static void 
fluid_render_loop_multithread(fluid_rvoice_mixer_t* mixer)
{
  int i, bufcount;
  //int scount = mixer->current_blockcount * FLUID_BUFSIZE;
  FLUID_DECLARE_VLA(fluid_real_t*, bufs, 
		    mixer->buffers.buf_count * 2 + mixer->buffers.fx_buf_count * 2);
  // How many threads should we start this time?
  int extra_threads = mixer->active_voices / VOICES_PER_THREAD;
  if (extra_threads > mixer->thread_count)
    extra_threads = mixer->thread_count;
  if (extra_threads == 0) {
    // No extra threads? No thread overhead!
    fluid_render_loop_singlethread(mixer);
    return;
  }

  bufcount = fluid_mixer_buffers_prepare(&mixer->buffers, bufs);
  
  // Prepare voice list
  fluid_cond_mutex_lock(mixer->wakeup_threads_m);
  fluid_atomic_int_set(&mixer->current_rvoice, 0);
  for (i=0; i < extra_threads; i++)
    fluid_atomic_int_set(&mixer->threads[i].ready, THREAD_BUF_PROCESSING);
  // Signal threads to wake up
  fluid_cond_broadcast(mixer->wakeup_threads);
  fluid_cond_mutex_unlock(mixer->wakeup_threads_m);
  
  // If thread is finished, mix it in
  while (fluid_mixer_mix_in(mixer, extra_threads)) {
    // Otherwise get a voice and render it
    fluid_rvoice_t* rvoice = fluid_mixer_get_mt_rvoice(mixer);
    if (rvoice != NULL) {
      fluid_profile_ref_var(prof_ref);
      fluid_mixer_buffers_render_one(&mixer->buffers, rvoice, bufs, bufcount);
      fluid_profile(FLUID_PROF_ONE_BLOCK_VOICE, prof_ref,1,
                    mixer->current_blockcount * FLUID_BUFSIZE);
      //test++;
    }
    else {
      // If no voices, wait for mixes. Make sure one is still processing to avoid deadlock
      int is_processing = 0;
      //waits++;
      fluid_cond_mutex_lock(mixer->thread_ready_m);
      for (i=0; i < extra_threads; i++) 
	if (fluid_atomic_int_get(&mixer->threads[i].ready) == 
	    THREAD_BUF_PROCESSING)
	  is_processing = 1;
      if (is_processing) 
        fluid_cond_wait(mixer->thread_ready, mixer->thread_ready_m);
      fluid_cond_mutex_unlock(mixer->thread_ready_m);
    }
  }
  //FLUID_LOG(FLUID_DBG, "Blockcount: %d, mixed %d of %d voices myself, waits = %d", 
  //	    mixer->current_blockcount, test, mixer->active_voices, waits);
}

static void delete_rvoice_mixer_threads(fluid_rvoice_mixer_t* mixer)
{
    int i;
    fluid_atomic_int_set(&mixer->threads_should_terminate, 1);
    // Signal threads to wake up
    fluid_cond_mutex_lock(mixer->wakeup_threads_m);
    for (i=0; i < mixer->thread_count; i++)
      fluid_atomic_int_set(&mixer->threads[i].ready, THREAD_BUF_TERMINATE);
    fluid_cond_broadcast(mixer->wakeup_threads);
    fluid_cond_mutex_unlock(mixer->wakeup_threads_m);
  
    for (i=0; i < mixer->thread_count; i++) {
      if (mixer->threads[i].thread) {
        fluid_thread_join(mixer->threads[i].thread);
        delete_fluid_thread(mixer->threads[i].thread);
      }
      fluid_mixer_buffers_free(&mixer->threads[i]);
    }
    FLUID_FREE(mixer->threads);
    mixer->thread_count = 0;
    mixer->threads = NULL;
}
#endif

/**
 * Update amount of extra mixer threads. 
 * @param thread_count Number of extra mixer threads for multi-core rendering
 * @param prio_level real-time prio level for the extra mixer threads
 */
DECLARE_FLUID_RVOICE_FUNCTION(fluid_rvoice_mixer_set_threads)
{
#if ENABLE_MIXER_THREADS
  char name[16];
  int i;
  fluid_rvoice_mixer_t* mixer = obj;
  int thread_count = param[0].i;
  int prio_level = param[1].real;
 
  // Kill all existing threads first
  if (mixer->thread_count)
  {
      delete_rvoice_mixer_threads(mixer);
  }
  
  if (thread_count == 0) 
    return;
  
  // Now prepare the new threads
  fluid_atomic_int_set(&mixer->threads_should_terminate, 0);
  mixer->threads = FLUID_ARRAY(fluid_mixer_buffers_t, thread_count);
  if (mixer->threads == NULL) {
    FLUID_LOG(FLUID_ERR, "Out of memory");
    return;
  }
  FLUID_MEMSET(mixer->threads, 0, thread_count*sizeof(fluid_mixer_buffers_t));
  mixer->thread_count = thread_count;
  for (i=0; i < thread_count; i++) {
    fluid_mixer_buffers_t* b = &mixer->threads[i]; 
    if (!fluid_mixer_buffers_init(b, mixer))
      return;
    fluid_atomic_int_set(&b->ready, THREAD_BUF_NODATA);
    FLUID_SNPRINTF (name, sizeof (name), "mixer%d", i);
    b->thread = new_fluid_thread(name, fluid_mixer_thread_func, b, prio_level, 0);
    if (!b->thread)
      return;
  }

#endif
}

/**
 * Synthesize audio into buffers
 * @param blockcount number of blocks to render, each having FLUID_BUFSIZE samples 
 * @return number of blocks rendered
 */
int 
fluid_rvoice_mixer_render(fluid_rvoice_mixer_t* mixer, int blockcount)
{
  fluid_profile_ref_var(prof_ref);
  
  mixer->current_blockcount = blockcount;

  // Zero buffers
  fluid_mixer_buffers_zero(&mixer->buffers);
  fluid_profile(FLUID_PROF_ONE_BLOCK_CLEAR, prof_ref, mixer->active_voices,
                mixer->current_blockcount * FLUID_BUFSIZE);
  
#if ENABLE_MIXER_THREADS
  if (mixer->thread_count > 0)
    fluid_render_loop_multithread(mixer);
  else
#endif
    fluid_render_loop_singlethread(mixer);
  fluid_profile(FLUID_PROF_ONE_BLOCK_VOICES, prof_ref, mixer->active_voices,
                mixer->current_blockcount * FLUID_BUFSIZE);
    

  // Process reverb & chorus
  fluid_rvoice_mixer_process_fx(mixer);

  // Call the callback and pack active voice array
  fluid_rvoice_mixer_process_finished_voices(mixer);

  return mixer->current_blockcount;
}
