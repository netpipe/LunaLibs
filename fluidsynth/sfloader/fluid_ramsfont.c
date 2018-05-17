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

#include "fluid_ramsfont.h"
#include "fluid_sys.h"
#include "fluid_synth.h"


/* Prototypes */
static int fluid_ramsfont_sfont_delete(fluid_sfont_t* sfont);
static const char *fluid_ramsfont_sfont_get_name(fluid_sfont_t* sfont);
static fluid_preset_t *fluid_ramsfont_sfont_get_preset(fluid_sfont_t* sfont,
                                                       int bank,
                                                       int prenum);
static void fluid_ramsfont_sfont_iteration_start(fluid_sfont_t* sfont);
static fluid_preset_t *fluid_ramsfont_sfont_iteration_next(fluid_sfont_t* sfont);
static void fluid_rampreset_preset_delete(fluid_preset_t* preset);
static const char *fluid_rampreset_preset_get_name(fluid_preset_t* preset);
static int fluid_rampreset_preset_get_banknum(fluid_preset_t* preset);
static int fluid_rampreset_preset_get_num(fluid_preset_t* preset);
static int fluid_rampreset_preset_noteon(fluid_preset_t* preset,
                                         fluid_synth_t* synth, int chan,
                                         int key, int vel);
static fluid_ramsfont_t *new_fluid_ramsfont (void);
static int delete_fluid_ramsfont (fluid_ramsfont_t* sfont);
static const char *fluid_ramsfont_get_name(fluid_ramsfont_t* sfont);
static int fluid_ramsfont_add_preset (fluid_ramsfont_t* sfont,
                                      fluid_rampreset_t* rampreset);
static fluid_preset_t *fluid_ramsfont_get_preset (fluid_ramsfont_t* sfont,
                                                     int bank, int num);
static void fluid_ramsfont_iteration_start (fluid_ramsfont_t* sfont);
static fluid_preset_t *fluid_ramsfont_iteration_next (fluid_ramsfont_t* sfont);
static fluid_rampreset_t* new_fluid_rampreset(fluid_ramsfont_t* sfont);
static void delete_fluid_rampreset (fluid_rampreset_t* preset);
static int fluid_rampreset_get_banknum (fluid_rampreset_t* preset);
static int fluid_rampreset_get_num (fluid_rampreset_t* preset);
static const char *fluid_rampreset_get_name (fluid_rampreset_t* preset);
static int fluid_rampreset_add_zone(fluid_rampreset_t* preset,
                                    fluid_preset_zone_t* zone);
static int fluid_rampreset_add_sample (fluid_rampreset_t* preset,
                                       fluid_sample_t* sample,
                                       int lokey, int hikey);
static fluid_inst_zone_t *fluid_rampreset_izoneforsample (fluid_rampreset_t* preset,
                                                          fluid_sample_t* sample);
static int fluid_rampreset_izone_set_loop (fluid_rampreset_t* preset,
                                           fluid_sample_t* sample,
                                           int on, float loopstart, float loopend);
static int fluid_rampreset_izone_set_gen (fluid_rampreset_t* preset,
                                          fluid_sample_t* sample,
                                          int gen_type, float value);
static int fluid_rampreset_remove_izone(fluid_rampreset_t* preset,
                                        fluid_sample_t* sample);
static int fluid_rampreset_remembervoice (fluid_rampreset_t* preset,
                                          fluid_voice_t* voice);
static void fluid_rampreset_updatevoices (fluid_rampreset_t* preset,
                                          int gen_type, float val);
static int fluid_rampreset_noteon (fluid_rampreset_t* preset, fluid_synth_t* synth,
                                   int chan, int key, int vel);


/**
 * Create a #fluid_sfont_t wrapping a #fluid_ramsfont_t
 * @return New #fluid_sfont_t or NULL if out of memory
 */
fluid_sfont_t*
fluid_ramsfont_create_sfont()
{
  fluid_sfont_t* sfont;
  fluid_ramsfont_t* ramsfont;

  ramsfont = new_fluid_ramsfont();
  if (ramsfont == NULL) {
    return NULL;
  }

  sfont = new_fluid_sfont(fluid_ramsfont_sfont_get_name,
                          fluid_ramsfont_sfont_get_preset,
                          fluid_ramsfont_sfont_delete);
  if (sfont == NULL)
  {
    delete_fluid_ramsfont(ramsfont);
    return NULL;
  }

  ramsfont->sfont = sfont;

  fluid_sfont_set_iteration_start(sfont, fluid_ramsfont_sfont_iteration_start);
  fluid_sfont_set_iteration_next(sfont, fluid_ramsfont_sfont_iteration_next);
  fluid_sfont_set_data(sfont, ramsfont);

  return sfont;
}

/* RAM SoundFont loader method to delete SoundFont */
static int
fluid_ramsfont_sfont_delete(fluid_sfont_t* sfont)
{
  if (delete_fluid_ramsfont(sfont->data) != 0)
    return -1;
  delete_fluid_sfont(sfont);
  return 0;
}

/* RAM SoundFont loader method to get name */
static const char *
fluid_ramsfont_sfont_get_name(fluid_sfont_t* sfont)
{
  return fluid_ramsfont_get_name((fluid_ramsfont_t*) sfont->data);
}

/* RAM SoundFont loader method to get a preset */
static fluid_preset_t *
fluid_ramsfont_sfont_get_preset(fluid_sfont_t* sfont, int bank, int prenum)
{
  return fluid_ramsfont_get_preset((fluid_ramsfont_t*) sfont->data, bank, prenum);
}

/* RAM SoundFont loader method to start preset iteration */
static void
fluid_ramsfont_sfont_iteration_start(fluid_sfont_t* sfont)
{
  fluid_ramsfont_iteration_start((fluid_ramsfont_t*) sfont->data);
}

/* RAM SoundFont loader method to advance preset iteration */
static fluid_preset_t*
fluid_ramsfont_sfont_iteration_next(fluid_sfont_t* sfont)
{
  return fluid_ramsfont_iteration_next((fluid_ramsfont_t*) sfont->data);
}

void fluid_rampreset_preset_delete(fluid_preset_t* preset)
{
  fluid_ramsfont_t* ramsfont;
  fluid_rampreset_t* rampreset;
  fluid_return_if_fail(preset != NULL);

  ramsfont = fluid_sfont_get_data(preset->sfont);
  rampreset = fluid_preset_get_data(preset);

  if (ramsfont)
  {
      ramsfont->preset = fluid_list_remove(ramsfont->preset, rampreset);
  }

  delete_fluid_rampreset(rampreset);
  delete_fluid_preset(preset);
}

/* RAM SoundFont loader get preset name method */
static const char *
fluid_rampreset_preset_get_name(fluid_preset_t* preset)
{
  return fluid_rampreset_get_name((fluid_rampreset_t*) preset->data);
}

/* RAM SoundFont loader get preset bank method */
static int
fluid_rampreset_preset_get_banknum(fluid_preset_t* preset)
{
  return fluid_rampreset_get_banknum((fluid_rampreset_t*) preset->data);
}

/* RAM SoundFont loader get preset program method */
static int
fluid_rampreset_preset_get_num(fluid_preset_t* preset)
{
  return fluid_rampreset_get_num((fluid_rampreset_t*) preset->data);
}

/* RAM SoundFont loader preset noteon method */
static int
fluid_rampreset_preset_noteon(fluid_preset_t* preset, fluid_synth_t* synth, int chan, int key, int vel)
{
  return fluid_rampreset_noteon((fluid_rampreset_t*) preset->data, synth, chan, key, vel);
}




/***************************************************************
 *
 *                           SFONT
 */

static fluid_ramsfont_t *
new_fluid_ramsfont (void)
{
  fluid_ramsfont_t* sfont;

  sfont = FLUID_NEW(fluid_ramsfont_t);
  if (sfont == NULL) {
    FLUID_LOG(FLUID_ERR, "Out of memory");
    return NULL;
  }

  sfont->name[0] = 0;
  sfont->sample = NULL;
  sfont->preset = NULL;

  return sfont;
}

static int
delete_fluid_ramsfont (fluid_ramsfont_t* sfont)
{
  fluid_list_t *list;
  fluid_preset_t* preset;
  fluid_return_val_if_fail(sfont != NULL, FLUID_OK);

  /* Check that no samples are currently used */
  for (list = sfont->sample; list; list = fluid_list_next(list)) {
    fluid_sample_t* sam = (fluid_sample_t*) fluid_list_get(list);
    if (sam->refcount != 0) {
      return -1;
    }
  }

  for (list = sfont->sample; list; list = fluid_list_next(list)) {
  	/* in ram soundfonts, the samples hold their data : so we should free it ourselves */
  	fluid_sample_t* sam = (fluid_sample_t*)fluid_list_get(list);
    delete_fluid_sample(sam);
  }

  if (sfont->sample) {
    delete_fluid_list(sfont->sample);
  }

  for (list = sfont->preset; list; list = fluid_list_next(list)) {
      preset = (fluid_preset_t *)fluid_list_get(list);
      fluid_rampreset_preset_delete(preset);
  }
  delete_fluid_list(sfont->preset);

  FLUID_FREE(sfont);
  return FLUID_OK;
}

static const char *
fluid_ramsfont_get_name(fluid_ramsfont_t* sfont)
{
  return sfont->name;
}

/**
 * Set a RAM SoundFont name.
 * @param sfont RAM SoundFont
 * @param name Name to assign (should be 20 chars in length with a NULL terminator)
 * @return #FLUID_OK
 */
int
fluid_ramsfont_set_name (fluid_ramsfont_t *sfont, const char *name)
{
  FLUID_MEMCPY(sfont->name, name, 20);
  return FLUID_OK;
}


/* Add a preset to a RAM SoundFont */
static int
fluid_ramsfont_add_preset (fluid_ramsfont_t* sfont, fluid_rampreset_t* rampreset)
{
  fluid_preset_t *preset;

  preset = new_fluid_preset(sfont->sfont,
                            fluid_rampreset_preset_get_name,
                            fluid_rampreset_preset_get_banknum,
                            fluid_rampreset_preset_get_num,
                            fluid_rampreset_preset_noteon,
                            fluid_rampreset_preset_delete); /* TODO: free modulators */
  if (preset == NULL) {
    return FLUID_FAILED;
  }
  fluid_preset_set_data(preset, rampreset);

  sfont->preset = fluid_list_append(sfont->preset, preset);

  return FLUID_OK;
}

/**
 * Creates one instrument zone for the sample inside the preset defined by
 * \a bank and \a num
 * @param sfont RAM SoundFont
 * @param bank Preset bank number
 * @param num Preset program number
 * @param sample Sample to use for instrument zone
 * @param lokey Lower MIDI key range of zone (0-127, <= \a hikey)
 * @param hikey Upper MIDI key range of zone (0-127, >= \a lokey)
 * @return #FLUID_OK on success, #FLUID_FAILED otherwise
 */
int
fluid_ramsfont_add_izone(fluid_ramsfont_t* sfont, int bank,
                         int num, fluid_sample_t* sample,
                         int lokey, int hikey)
{
	/*- find or create a preset
		- add it the sample using the fluid_rampreset_add_sample fucntion
		- add the sample to the list of samples
	*/
	int err;

    fluid_rampreset_t* rampreset;
	fluid_preset_t* preset = fluid_ramsfont_get_preset(sfont, bank, num);
	if (preset == NULL) {
		// Create it
		rampreset = new_fluid_rampreset(sfont);
		if (rampreset == NULL) {
			return FLUID_FAILED;
		}

		rampreset->bank = bank;
		rampreset->num = num;

		// sort the preset
		fluid_ramsfont_add_preset(sfont, rampreset);

		err = fluid_rampreset_add_sample(rampreset, sample, lokey, hikey);
		if (err != FLUID_OK) {
            // MWE: delete preset (also check that all preset delete also remove list item!)
            fluid_rampreset_preset_delete(preset);
			return FLUID_FAILED;
		}


	} else {

		// just add it
        rampreset = fluid_preset_get_data(preset);
		err = fluid_rampreset_add_sample(rampreset, sample, lokey, hikey);
		if (err != FLUID_OK) {
			return FLUID_FAILED;
		}
	}

  sfont->sample = fluid_list_append(sfont->sample, sample);
  return FLUID_OK;
}

/**
 * Removes the instrument zone corresponding to \a bank, \a num and \a sample
 * @param sfont RAM SoundFont
 * @param bank Preset bank number
 * @param num Preset program number
 * @param sample Sample of the preset zone
 * @return #FLUID_OK on success, #FLUID_FAILED otherwise
 */
int
fluid_ramsfont_remove_izone (fluid_ramsfont_t* sfont, int bank,
                             int num, fluid_sample_t* sample)
{
	int err;
    fluid_rampreset_t *rampreset;
	fluid_preset_t* preset = fluid_ramsfont_get_preset(sfont, bank, num);
	if (preset == NULL) {
		return FLUID_FAILED;
	}

    rampreset = fluid_preset_get_data(preset);

	// Fixed a crash bug : remove the sample from the sfont list after
	// removing the izone (aschmitt august 2005)
	err = fluid_rampreset_remove_izone(rampreset, sample);
	if (err != FLUID_OK)
		return err;

	// now we must remove the sample from sfont->sample
	sfont->sample = fluid_list_remove(sfont->sample, sample);

	return FLUID_OK;
}

/**
 * Sets a generator on an instrument zone identified by \a bank, \a num and \a sample
 * @param sfont RAM SoundFont
 * @param bank Preset bank number
 * @param num Preset program number
 * @param sample Sample of the instrument zone.
 * @param gen_type Generator ID (#fluid_gen_type)
 * @param value Generator value
 * @return #FLUID_OK on success, #FLUID_FAILED otherwise
 */
int
fluid_ramsfont_izone_set_gen (fluid_ramsfont_t* sfont, int bank,
                              int num, fluid_sample_t* sample,
                              int gen_type, float value)
{
    fluid_rampreset_t* rampreset;
	fluid_preset_t* preset = fluid_ramsfont_get_preset(sfont, bank, num);
	if (preset == NULL) {
			return FLUID_FAILED;
	}

    rampreset = fluid_preset_get_data(preset);

	return fluid_rampreset_izone_set_gen(rampreset, sample, gen_type, value);
}

/**
 * Sets loop start/end values of the instrument zone identified by \a bank,
 * \a num and \a sample.
 * @param sfont RAM SoundFont
 * @param bank Preset bank number
 * @param num Preset program number
 * @param sample Sample of the instrument zone
 * @param on TRUE to enable looping, FALSE for one shot (\a loopstart and \a loopend
 *   not used)
 * @param loopstart Loop start, in frames (counted from 0)
 * @param loopend Loop end, in frames (counted from last frame, thus is < 0)
 * @return #FLUID_OK on success, #FLUID_FAILED otherwise
 */
int
fluid_ramsfont_izone_set_loop (fluid_ramsfont_t *sfont, int bank,
                               int num, fluid_sample_t* sample,
                               int on, float loopstart, float loopend)
{
    fluid_rampreset_t* rampreset;
	fluid_preset_t* preset = fluid_ramsfont_get_preset(sfont, bank, num);
	if (preset == NULL) {
			return FLUID_FAILED;
	}

    rampreset = fluid_preset_get_data(preset);

	return fluid_rampreset_izone_set_loop(rampreset, sample, on, loopstart, loopend);
}

/* Get a preset from a RAM SoundFont */
static fluid_preset_t *
fluid_ramsfont_get_preset (fluid_ramsfont_t* sfont, int bank, int num)
{
    fluid_preset_t *preset;
    fluid_list_t *list;

    for(list = sfont->preset; list != NULL; list = fluid_list_next(list))
    {
        preset = (fluid_preset_t *)fluid_list_get(list);

        if ((fluid_preset_get_banknum(preset) == bank) && (fluid_preset_get_num(preset) == num))
        {
            return preset;
        }
    }

    return NULL;
}

/* Start preset iteration in a RAM SoundFont */
static void
fluid_ramsfont_iteration_start (fluid_ramsfont_t* sfont)
{
  sfont->preset_iter_cur = sfont->preset;
}

/* Advance preset iteration in a RAM SoundFont */
static fluid_preset_t *
fluid_ramsfont_iteration_next (fluid_ramsfont_t* sfont)
{
  fluid_preset_t *preset = (fluid_preset_t *)fluid_list_get(sfont->preset_iter_cur);

  sfont->preset_iter_cur = fluid_list_next(sfont->preset_iter_cur);

  return preset;
}

/***************************************************************
 *
 *                           PRESET
 */

typedef struct _fluid_rampreset_voice_t fluid_rampreset_voice_t;
struct _fluid_rampreset_voice_t {
	fluid_voice_t *voice;
	unsigned int voiceID;
};

/* Create a new RAM SoundFont preset */
static fluid_rampreset_t*
new_fluid_rampreset(fluid_ramsfont_t* sfont)
{
  fluid_rampreset_t* preset = FLUID_NEW(fluid_rampreset_t);
  if (preset == NULL) {
    FLUID_LOG(FLUID_ERR, "Out of memory");
    return NULL;
  }
  preset->next = NULL;
  preset->sfont = sfont;
  preset->name[0] = 0;
  preset->bank = 0;
  preset->num = 0;
  preset->global_zone = NULL;
  preset->zone = NULL;
  preset->presetvoices = NULL;
  return preset;
}

/* Delete a RAM SoundFont preset */
static void
delete_fluid_rampreset (fluid_rampreset_t* preset)
{
  fluid_preset_zone_t* zone;
  fluid_rampreset_voice_t *data;
  fluid_return_if_fail(preset != NULL);

  if (preset->global_zone != NULL) {
    delete_fluid_preset_zone(preset->global_zone);
    preset->global_zone = NULL;
  }
  zone = preset->zone;
  while (zone != NULL) {
    preset->zone = zone->next;
    delete_fluid_preset_zone(zone);
    zone = preset->zone;
  }

  if (preset->presetvoices != NULL) {
  	fluid_list_t *tmp = preset->presetvoices, *next;
  	while (tmp) {
  		data = (fluid_rampreset_voice_t *)(tmp->data);
  		FLUID_FREE(data);

  		next = tmp->next;
  		FLUID_FREE(tmp);
  		tmp = next;
  	}
  }
  preset->presetvoices = NULL;

  FLUID_FREE(preset);
}

/* Get a RAM SoundFont preset bank */
static int
fluid_rampreset_get_banknum (fluid_rampreset_t* preset)
{
  return preset->bank;
}

/* Get a RAM SoundFont preset program */
static int
fluid_rampreset_get_num (fluid_rampreset_t* preset)
{
  return preset->num;
}

/* Get a RAM SoundFont preset name */
static const char *
fluid_rampreset_get_name (fluid_rampreset_t* preset)
{
  return preset->name;
}


/* Add a zone to a RAM SoundFont preset */
static int
fluid_rampreset_add_zone(fluid_rampreset_t* preset, fluid_preset_zone_t* zone)
{
  if (preset->zone == NULL) {
    zone->next = NULL;
    preset->zone = zone;
  } else {
    zone->next = preset->zone;
    preset->zone = zone;
  }
  return FLUID_OK;
}

/* Add a sample to a RAM SoundFont preset */
static int
fluid_rampreset_add_sample (fluid_rampreset_t* preset, fluid_sample_t* sample,
                            int lokey, int hikey)
{
	/* create a new instrument zone, with the given sample */

	/* one preset zone */
	if (preset->zone == NULL) {
		fluid_preset_zone_t* zone;
		zone = new_fluid_preset_zone("");
		if (zone == NULL) {
			return FLUID_FAILED;
		}

		/* its instrument */
		zone->inst = (fluid_inst_t*) new_fluid_inst();
    if (zone->inst == NULL) {
      delete_fluid_preset_zone(zone);
      return FLUID_FAILED;
    }

		fluid_rampreset_add_zone(preset, zone);
	}

	/* add an instrument zone for each sample */
	{
		fluid_inst_t* inst = fluid_preset_zone_get_inst(preset->zone);
		fluid_inst_zone_t* izone = new_fluid_inst_zone("");
		if (izone == NULL) {
			return FLUID_FAILED;
		}

		if (fluid_inst_add_zone(inst, izone) != FLUID_OK) {
			delete_fluid_inst_zone(izone);
			return FLUID_FAILED;
		}

		izone->sample = sample;
		izone->range.keylo = lokey;
		izone->range.keyhi = hikey;

		// give the preset the name of the sample
		FLUID_MEMCPY(preset->name, sample->name, 20);
	}

	return FLUID_OK;
}

/* Find an instrument zone with the given sample */
static fluid_inst_zone_t *
fluid_rampreset_izoneforsample (fluid_rampreset_t* preset, fluid_sample_t* sample)
{
	fluid_inst_t* inst;
	fluid_inst_zone_t* izone;

	if (preset->zone == NULL) return NULL;

	inst = fluid_preset_zone_get_inst(preset->zone);
	izone = inst->zone;
	while (izone) {
		if (izone->sample == sample)
			return izone;
		izone = izone->next;
	}
	return NULL;
}

/* Set loop of an instrument zone */
static int
fluid_rampreset_izone_set_loop (fluid_rampreset_t* preset, fluid_sample_t* sample,
                                int on, float loopstart, float loopend)
{
	fluid_inst_zone_t* izone = fluid_rampreset_izoneforsample(preset, sample);
	short coarse, fine;

	if (izone == NULL)
			return FLUID_FAILED;

	if (!on) {
		izone->gen[GEN_SAMPLEMODE].flags = GEN_SET;
		izone->gen[GEN_SAMPLEMODE].val = FLUID_UNLOOPED;
		fluid_rampreset_updatevoices(preset, GEN_SAMPLEMODE, FLUID_UNLOOPED);
		return FLUID_OK;
	}

	/* NOTE : We should check that (sample->startloop + loopStart <= sample->endloop - loopend - 32) */

	/* loopstart */
	if (loopstart > 32767. || loopstart < -32767.) {
		coarse = (short)(loopstart/32768.);
		fine = (short)(loopstart - (float)(coarse)*32768.);
	} else {
		coarse = 0;
		fine = (short)loopstart;
	}
	izone->gen[GEN_STARTLOOPADDROFS].flags = GEN_SET;
	izone->gen[GEN_STARTLOOPADDROFS].val = fine;
	fluid_rampreset_updatevoices(preset, GEN_STARTLOOPADDROFS, fine);
	if (coarse) {
		izone->gen[GEN_STARTLOOPADDRCOARSEOFS].flags = GEN_SET;
		izone->gen[GEN_STARTLOOPADDRCOARSEOFS].val = coarse;
	} else {
		izone->gen[GEN_STARTLOOPADDRCOARSEOFS].flags = GEN_UNUSED;
	}
	fluid_rampreset_updatevoices(preset, GEN_STARTLOOPADDRCOARSEOFS, coarse);

	/* loopend */
	if (loopend > 32767. || loopend < -32767.) {
		coarse = (short)(loopend/32768.);
		fine = (short)(loopend - (float)(coarse)*32768.);
	} else {
		coarse = 0;
		fine = (short)loopend;
	}
	izone->gen[GEN_ENDLOOPADDROFS].flags = GEN_SET;
	izone->gen[GEN_ENDLOOPADDROFS].val = fine;
	fluid_rampreset_updatevoices(preset, GEN_ENDLOOPADDROFS, fine);
	if (coarse) {
		izone->gen[GEN_ENDLOOPADDRCOARSEOFS].flags = GEN_SET;
		izone->gen[GEN_ENDLOOPADDRCOARSEOFS].val = coarse;
	} else {
		izone->gen[GEN_ENDLOOPADDRCOARSEOFS].flags = GEN_UNUSED;
	}
	fluid_rampreset_updatevoices(preset, GEN_ENDLOOPADDRCOARSEOFS, coarse);

	izone->gen[GEN_SAMPLEMODE].flags = GEN_SET;
	izone->gen[GEN_SAMPLEMODE].val = FLUID_LOOP_DURING_RELEASE;
	fluid_rampreset_updatevoices(preset, GEN_SAMPLEMODE, FLUID_LOOP_DURING_RELEASE);

	/* If the loop points are the whole samples, we are supposed to
	   copy the frames around in the margins (the start to the end margin and
	   the end to the start margin), but it works fine without this. Maybe some time
	   it will be needed (see SAMPLE_LOOP_MARGIN) -- Antoie Schmitt May 2003 */

	return FLUID_OK;
}

/* Set a generator on the instrument zone in preset having sample */
static int
fluid_rampreset_izone_set_gen (fluid_rampreset_t* preset, fluid_sample_t* sample,
                               int gen_type, float value)
{
	fluid_inst_zone_t* izone = fluid_rampreset_izoneforsample(preset, sample);
	if (izone == NULL)
			return FLUID_FAILED;

	izone->gen[gen_type].flags = GEN_SET;
	izone->gen[gen_type].val = value;

	fluid_rampreset_updatevoices(preset, gen_type, value);

	return FLUID_OK;
}

/* Remove the instrument zone from preset having sample */
static int
fluid_rampreset_remove_izone(fluid_rampreset_t* preset, fluid_sample_t* sample)
{
	fluid_inst_t* inst;
	fluid_inst_zone_t* izone, * prev;
	int found = 0;

	if (preset->zone == NULL) return FLUID_FAILED;
	inst = fluid_preset_zone_get_inst(preset->zone);
	izone = inst->zone;
	prev = NULL;
	while (izone && !found) {
		if (izone->sample == sample) {
			if (prev == NULL) {
				inst->zone = izone->next;
			} else {
				prev->next = izone->next;
			}
			izone->next = NULL;
			delete_fluid_inst_zone(izone);
			found = 1;
		} else {
			prev = izone;
			izone = izone->next;
		}
	}
	if (!found)
		return FLUID_FAILED;

	// stop all the voices that use this sample, so that
	// the sample can be cleared up
	{
		fluid_list_t *tmp = preset->presetvoices;
		while (tmp) {
			fluid_rampreset_voice_t *presetvoice = (fluid_rampreset_voice_t *)(tmp->data);
			fluid_voice_t *voice = presetvoice->voice;
			if (fluid_voice_is_playing(voice) && (fluid_voice_get_id(voice) == presetvoice->voiceID)) {
				// still belongs to the preset
				if (voice->sample == sample) {
					// uses this sample : turn it off.
					// our presetvoices struct will be cleaneup at the next update
					fluid_voice_off(voice);
				}
			}
			tmp = tmp->next;
		}
	}
	return FLUID_OK;
}

/* Stores the voice and the its ID in the preset for later update on gen_set */
static int
fluid_rampreset_remembervoice (fluid_rampreset_t* preset, fluid_voice_t* voice)
{
  fluid_rampreset_voice_t *presetvoice = FLUID_NEW(fluid_rampreset_voice_t);
  if (presetvoice == NULL) {
    FLUID_LOG(FLUID_ERR, "Out of memory");
    return FLUID_FAILED;
  }

  presetvoice->voice = voice;
  presetvoice->voiceID = fluid_voice_get_id(voice);

  preset->presetvoices = fluid_list_append(preset->presetvoices, (void *)presetvoice);
  if (preset->presetvoices == NULL) {
  	FLUID_FREE(presetvoice);
    FLUID_LOG(FLUID_ERR, "Out of memory");
    return FLUID_FAILED;
  }
  return FLUID_OK;
}

/* Update a generator in realtime for a preset */
static void
fluid_rampreset_updatevoices (fluid_rampreset_t* preset, int gen_type, float val)
{
	fluid_list_t *tmp = preset->presetvoices, *prev = NULL, *next;

	/* Walk the presetvoice to update them if they are still active and ours.
	 * If their ID has changed or their state is not playing, they are not
	 * ours, so we forget them. */
	while (tmp) {
		fluid_rampreset_voice_t *presetvoice = (fluid_rampreset_voice_t *)(tmp->data);
		fluid_voice_t *voice = presetvoice->voice;
		if (!fluid_voice_is_playing(voice) || (fluid_voice_get_id(voice) != presetvoice->voiceID)) {
			/* forget it */
  		FLUID_FREE(presetvoice);

			/* unlink it */
			next = tmp->next;
  		FLUID_FREE(tmp);
			if (prev) {
				prev->next = next;
			} else {
				preset->presetvoices = next;
			}
  		tmp = next;

		} else {

			/* update */
			fluid_voice_gen_set(voice, gen_type, val);
			fluid_voice_update_param(voice, gen_type);

			/* next */
			prev = tmp;
			tmp = tmp->next;
		}
	}
}


/* RAM SoundFont preset note on */
static int
fluid_rampreset_noteon (fluid_rampreset_t* preset, fluid_synth_t* synth, int chan,
                        int key, int vel)
{
  fluid_preset_zone_t *preset_zone;
  fluid_inst_t* inst;
  fluid_inst_zone_t *inst_zone, *global_inst_zone;
  fluid_sample_t* sample;
  fluid_voice_t* voice;
  fluid_mod_t * mod;
  fluid_mod_t * mod_list[FLUID_NUM_MOD]; /* list for 'sorting' preset modulators */
  int mod_list_count;
  int i;

  /* run thru all the zones of this preset */
  preset_zone = preset->zone;
  while (preset_zone != NULL) {

    /* check if the note falls into the key and velocity range of this
       preset */
    if (fluid_zone_inside_range(&preset_zone->range, key, vel)) {

      inst = fluid_preset_zone_get_inst(preset_zone);
      global_inst_zone = fluid_inst_get_global_zone(inst);

      /* run thru all the zones of this instrument */
      inst_zone = fluid_inst_get_zone(inst);
      while (inst_zone != NULL) {
          
	/* make sure this instrument zone has a valid sample */
	sample = fluid_inst_zone_get_sample(inst_zone);
	if ((sample == NULL) || fluid_sample_in_rom(sample)) {
	  inst_zone = fluid_inst_zone_next(inst_zone);
	  continue;
	}

	/* check if the instrument zone doesn't be ignored and the note falls into
	   the key and velocity range of this  instrument zone.
	   An instrument zone must be ignored when its voice is already running
	   played by a legato passage (see fluid_synth_noteon_monopoly_legato()) */
	if (fluid_zone_inside_range(&inst_zone->range, key, vel)) {

	  /* this is a good zone. allocate a new synthesis process and initialize it */
	  voice = fluid_synth_alloc_voice_LOCAL(synth, sample, chan, key, vel, &inst_zone->range);
	  if (voice == NULL) {
	    return FLUID_FAILED;
	  }

	  if (fluid_rampreset_remembervoice(preset, voice) != FLUID_OK) {
	    return FLUID_FAILED;
	  }

	  /* Instrument level, generators */

	  for (i = 0; i < GEN_LAST; i++) {

	    /* SF 2.01 section 9.4 'bullet' 4:
	     *
	     * A generator in a local instrument zone supersedes a
	     * global instrument zone generator.  Both cases supersede
	     * the default generator -> voice_gen_set */

	    if (inst_zone->gen[i].flags){
	      fluid_voice_gen_set(voice, i, inst_zone->gen[i].val);

	    } else if (global_inst_zone != NULL && global_inst_zone->gen[i].flags){
	      fluid_voice_gen_set(voice, i, global_inst_zone->gen[i].val);

	    } else {
	      /* The generator has not been defined in this instrument.
	       * Do nothing, leave it at the default.
	       */
	    };

	  }; /* for all generators */

	  /* global instrument zone, modulators: Put them all into a
	   * list. */

	  mod_list_count = 0;

	  if (global_inst_zone){
	    mod = global_inst_zone->mod;
	    while (mod){
	      mod_list[mod_list_count++] = mod;
	      mod = mod->next;
	    };
	  };

	  /* local instrument zone, modulators.
	   * Replace modulators with the same definition in the list:
	   * SF 2.01 page 69, 'bullet' 8
	   */
	  mod = inst_zone->mod;

	  while (mod){

	    /* 'Identical' modulators will be deleted by setting their
	     *  list entry to NULL.  The list length is known, NULL
	     *  entries will be ignored later.  SF2.01 section 9.5.1
	     *  page 69, 'bullet' 3 defines 'identical'.  */

	    for (i = 0; i < mod_list_count; i++){
	      if (fluid_mod_test_identity(mod,mod_list[i])){
		mod_list[i] = NULL;
	      };
	    };

	    /* Finally add the new modulator to to the list. */
	    mod_list[mod_list_count++] = mod;
	    mod = mod->next;
	  };

	  /* Add instrument modulators (global / local) to the voice. */
	  for (i = 0; i < mod_list_count; i++){

	    mod = mod_list[i];

	    if (mod != NULL){ /* disabled modulators CANNOT be skipped. */

	      /* Instrument modulators -supersede- existing (default)
	       * modulators.  SF 2.01 page 69, 'bullet' 6 */
	      fluid_voice_add_mod(voice, mod, FLUID_VOICE_OVERWRITE);
	    };
	  };

	  /* Preset level, generators */

	  for (i = 0; i < GEN_LAST; i++) {

	    /* SF 2.01 section 8.5 page 58: If some generators are
	     * encountered at preset level, they should be ignored */
	    if ((i != GEN_STARTADDROFS)
		&& (i != GEN_ENDADDROFS)
		&& (i != GEN_STARTLOOPADDROFS)
		&& (i != GEN_ENDLOOPADDROFS)
		&& (i != GEN_STARTADDRCOARSEOFS)
		&& (i != GEN_ENDADDRCOARSEOFS)
		&& (i != GEN_STARTLOOPADDRCOARSEOFS)
		&& (i != GEN_KEYNUM)
		&& (i != GEN_VELOCITY)
		&& (i != GEN_ENDLOOPADDRCOARSEOFS)
		&& (i != GEN_SAMPLEMODE)
		&& (i != GEN_EXCLUSIVECLASS)
		&& (i != GEN_OVERRIDEROOTKEY)) {

	      /* SF 2.01 section 9.4 'bullet' 9: A generator in a
	       * local preset zone supersedes a global preset zone
	       * generator.  The effect is -added- to the destination
	       * summing node -> voice_gen_incr */

	      if (preset_zone->gen[i].flags){
		fluid_voice_gen_incr(voice, i, preset_zone->gen[i].val);
	      } else {
		/* The generator has not been defined in this preset
		 * Do nothing, leave it unchanged.
		 */
	      };
	    }; /* if available at preset level */
	  }; /* for all generators */


	  /* Global preset zone, modulators: put them all into a
	   * list. */
	  mod_list_count = 0;

	  /* Process the modulators of the local preset zone.  Kick
	   * out all identical modulators from the global preset zone
	   * (SF 2.01 page 69, second-last bullet) */

	  mod = preset_zone->mod;
	  while (mod){
	    for (i = 0; i < mod_list_count; i++){
	      if (fluid_mod_test_identity(mod,mod_list[i])){
		mod_list[i] = NULL;
	      };
	    };

	    /* Finally add the new modulator to the list. */
	    mod_list[mod_list_count++] = mod;
	    mod = mod->next;
	  };

	  /* Add preset modulators (global / local) to the voice. */
	  for (i = 0; i < mod_list_count; i++){
	    mod = mod_list[i];
	    if ((mod != NULL) && (mod->amount != 0)) { /* disabled modulators can be skipped. */

	      /* Preset modulators -add- to existing instrument /
	       * default modulators.  SF2.01 page 70 first bullet on
	       * page */
	      fluid_voice_add_mod(voice, mod, FLUID_VOICE_ADD);
	    };
	  };

	  /* add the synthesis process to the synthesis loop. */
	  fluid_synth_start_voice(synth, voice);

	  /* Store the ID of the first voice that was created by this noteon event.
	   * Exclusive class may only terminate older voices.
	   * That avoids killing voices, which have just been created.
	   * (a noteon event can create several voice processes with the same exclusive
	   * class - for example when using stereo samples)
	   */
	}

	inst_zone = fluid_inst_zone_next(inst_zone);
      }
    }
    preset_zone = fluid_preset_zone_next(preset_zone);
  }

  return FLUID_OK;
}