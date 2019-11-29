/* ----------------------------------------------------------------------------
 * This file was automatically generated by SWIG (http://www.swig.org).
 * Version 2.0.4
 *
 * Do not make changes to this file unless you know what you are doing--modify
 * the SWIG interface file instead.
 * ----------------------------------------------------------------------------- */

namespace cAudio {

using System;
using System.Runtime.InteropServices;

public class IAudioSource : IRefCounted {
  private HandleRef swigCPtr;

  internal IAudioSource(IntPtr cPtr, bool cMemoryOwn) : base(cAudioCSharpWrapperPINVOKE.IAudioSource_SWIGUpcast(cPtr), cMemoryOwn) {
    swigCPtr = new HandleRef(this, cPtr);
  }

  internal static HandleRef getCPtr(IAudioSource obj) {
    return (obj == null) ? new HandleRef(null, IntPtr.Zero) : obj.swigCPtr;
  }

  ~IAudioSource() {
    Dispose();
  }

  public override void Dispose() {
    lock(this) {
      if (swigCPtr.Handle != IntPtr.Zero) {
        if (swigCMemOwn) {
          swigCMemOwn = false;
          cAudioCSharpWrapperPINVOKE.delete_IAudioSource(swigCPtr);
        }
        swigCPtr = new HandleRef(null, IntPtr.Zero);
      }
      GC.SuppressFinalize(this);
      base.Dispose();
    }
  }

  public virtual bool play() {
    bool ret = cAudioCSharpWrapperPINVOKE.IAudioSource_play(swigCPtr);
    return ret;
  }

  public virtual bool play2d(bool toLoop) {
    bool ret = cAudioCSharpWrapperPINVOKE.IAudioSource_play2d__SWIG_0(swigCPtr, toLoop);
    return ret;
  }

  public virtual bool play2d() {
    bool ret = cAudioCSharpWrapperPINVOKE.IAudioSource_play2d__SWIG_1(swigCPtr);
    return ret;
  }

  public virtual bool play3d(cVector3 position, float soundstr, bool toLoop) {
    bool ret = cAudioCSharpWrapperPINVOKE.IAudioSource_play3d__SWIG_0(swigCPtr, cVector3.getCPtr(position), soundstr, toLoop);
    if (cAudioCSharpWrapperPINVOKE.SWIGPendingException.Pending) throw cAudioCSharpWrapperPINVOKE.SWIGPendingException.Retrieve();
    return ret;
  }

  public virtual bool play3d(cVector3 position, float soundstr) {
    bool ret = cAudioCSharpWrapperPINVOKE.IAudioSource_play3d__SWIG_1(swigCPtr, cVector3.getCPtr(position), soundstr);
    if (cAudioCSharpWrapperPINVOKE.SWIGPendingException.Pending) throw cAudioCSharpWrapperPINVOKE.SWIGPendingException.Retrieve();
    return ret;
  }

  public virtual bool play3d(cVector3 position) {
    bool ret = cAudioCSharpWrapperPINVOKE.IAudioSource_play3d__SWIG_2(swigCPtr, cVector3.getCPtr(position));
    if (cAudioCSharpWrapperPINVOKE.SWIGPendingException.Pending) throw cAudioCSharpWrapperPINVOKE.SWIGPendingException.Retrieve();
    return ret;
  }

  public virtual void pause() {
    cAudioCSharpWrapperPINVOKE.IAudioSource_pause(swigCPtr);
  }

  public virtual void stop() {
    cAudioCSharpWrapperPINVOKE.IAudioSource_stop(swigCPtr);
  }

  public virtual void loop(bool toLoop) {
    cAudioCSharpWrapperPINVOKE.IAudioSource_loop(swigCPtr, toLoop);
  }

  public virtual bool seek(float seconds, bool relative) {
    bool ret = cAudioCSharpWrapperPINVOKE.IAudioSource_seek__SWIG_0(swigCPtr, seconds, relative);
    return ret;
  }

  public virtual bool seek(float seconds) {
    bool ret = cAudioCSharpWrapperPINVOKE.IAudioSource_seek__SWIG_1(swigCPtr, seconds);
    return ret;
  }

  public virtual float getTotalAudioTime() {
    float ret = cAudioCSharpWrapperPINVOKE.IAudioSource_getTotalAudioTime(swigCPtr);
    return ret;
  }

  public virtual int getTotalAudioSize() {
    int ret = cAudioCSharpWrapperPINVOKE.IAudioSource_getTotalAudioSize(swigCPtr);
    return ret;
  }

  public virtual int getCompressedAudioSize() {
    int ret = cAudioCSharpWrapperPINVOKE.IAudioSource_getCompressedAudioSize(swigCPtr);
    return ret;
  }

  public virtual float getCurrentAudioTime() {
    float ret = cAudioCSharpWrapperPINVOKE.IAudioSource_getCurrentAudioTime(swigCPtr);
    return ret;
  }

  public virtual int getCurrentAudioPosition() {
    int ret = cAudioCSharpWrapperPINVOKE.IAudioSource_getCurrentAudioPosition(swigCPtr);
    return ret;
  }

  public virtual int getCurrentCompressedAudioPosition() {
    int ret = cAudioCSharpWrapperPINVOKE.IAudioSource_getCurrentCompressedAudioPosition(swigCPtr);
    return ret;
  }

  public virtual bool update() {
    bool ret = cAudioCSharpWrapperPINVOKE.IAudioSource_update(swigCPtr);
    return ret;
  }

  public virtual bool isValid() {
    bool ret = cAudioCSharpWrapperPINVOKE.IAudioSource_isValid(swigCPtr);
    return ret;
  }

  public virtual bool isPlaying() {
    bool ret = cAudioCSharpWrapperPINVOKE.IAudioSource_isPlaying(swigCPtr);
    return ret;
  }

  public virtual bool isPaused() {
    bool ret = cAudioCSharpWrapperPINVOKE.IAudioSource_isPaused(swigCPtr);
    return ret;
  }

  public virtual bool isStopped() {
    bool ret = cAudioCSharpWrapperPINVOKE.IAudioSource_isStopped(swigCPtr);
    return ret;
  }

  public virtual bool isLooping() {
    bool ret = cAudioCSharpWrapperPINVOKE.IAudioSource_isLooping(swigCPtr);
    return ret;
  }

  public virtual void setPosition(cVector3 position) {
    cAudioCSharpWrapperPINVOKE.IAudioSource_setPosition(swigCPtr, cVector3.getCPtr(position));
    if (cAudioCSharpWrapperPINVOKE.SWIGPendingException.Pending) throw cAudioCSharpWrapperPINVOKE.SWIGPendingException.Retrieve();
  }

  public virtual void setVelocity(cVector3 velocity) {
    cAudioCSharpWrapperPINVOKE.IAudioSource_setVelocity(swigCPtr, cVector3.getCPtr(velocity));
    if (cAudioCSharpWrapperPINVOKE.SWIGPendingException.Pending) throw cAudioCSharpWrapperPINVOKE.SWIGPendingException.Retrieve();
  }

  public virtual void setDirection(cVector3 direction) {
    cAudioCSharpWrapperPINVOKE.IAudioSource_setDirection(swigCPtr, cVector3.getCPtr(direction));
    if (cAudioCSharpWrapperPINVOKE.SWIGPendingException.Pending) throw cAudioCSharpWrapperPINVOKE.SWIGPendingException.Retrieve();
  }

  public virtual void setRolloffFactor(float rolloff) {
    cAudioCSharpWrapperPINVOKE.IAudioSource_setRolloffFactor(swigCPtr, rolloff);
  }

  public virtual void setStrength(float soundstrength) {
    cAudioCSharpWrapperPINVOKE.IAudioSource_setStrength(swigCPtr, soundstrength);
  }

  public virtual void setMinDistance(float minDistance) {
    cAudioCSharpWrapperPINVOKE.IAudioSource_setMinDistance(swigCPtr, minDistance);
  }

  public virtual void setMaxDistance(float maxDistance) {
    cAudioCSharpWrapperPINVOKE.IAudioSource_setMaxDistance(swigCPtr, maxDistance);
  }

  public virtual void setPitch(float pitch) {
    cAudioCSharpWrapperPINVOKE.IAudioSource_setPitch(swigCPtr, pitch);
  }

  public virtual void setVolume(float volume) {
    cAudioCSharpWrapperPINVOKE.IAudioSource_setVolume(swigCPtr, volume);
  }

  public virtual void setMinVolume(float minVolume) {
    cAudioCSharpWrapperPINVOKE.IAudioSource_setMinVolume(swigCPtr, minVolume);
  }

  public virtual void setMaxVolume(float maxVolume) {
    cAudioCSharpWrapperPINVOKE.IAudioSource_setMaxVolume(swigCPtr, maxVolume);
  }

  public virtual void setInnerConeAngle(float innerAngle) {
    cAudioCSharpWrapperPINVOKE.IAudioSource_setInnerConeAngle(swigCPtr, innerAngle);
  }

  public virtual void setOuterConeAngle(float outerAngle) {
    cAudioCSharpWrapperPINVOKE.IAudioSource_setOuterConeAngle(swigCPtr, outerAngle);
  }

  public virtual void setOuterConeVolume(float outerVolume) {
    cAudioCSharpWrapperPINVOKE.IAudioSource_setOuterConeVolume(swigCPtr, outerVolume);
  }

  public virtual void setDopplerStrength(float dstrength) {
    cAudioCSharpWrapperPINVOKE.IAudioSource_setDopplerStrength(swigCPtr, dstrength);
  }

  public virtual void setDopplerVelocity(cVector3 dvelocity) {
    cAudioCSharpWrapperPINVOKE.IAudioSource_setDopplerVelocity(swigCPtr, cVector3.getCPtr(dvelocity));
    if (cAudioCSharpWrapperPINVOKE.SWIGPendingException.Pending) throw cAudioCSharpWrapperPINVOKE.SWIGPendingException.Retrieve();
  }

  public virtual void move(cVector3 position) {
    cAudioCSharpWrapperPINVOKE.IAudioSource_move(swigCPtr, cVector3.getCPtr(position));
    if (cAudioCSharpWrapperPINVOKE.SWIGPendingException.Pending) throw cAudioCSharpWrapperPINVOKE.SWIGPendingException.Retrieve();
  }

  public virtual cVector3 getPosition() {
    cVector3 ret = new cVector3(cAudioCSharpWrapperPINVOKE.IAudioSource_getPosition(swigCPtr), true);
    return ret;
  }

  public virtual cVector3 getVelocity() {
    cVector3 ret = new cVector3(cAudioCSharpWrapperPINVOKE.IAudioSource_getVelocity(swigCPtr), true);
    return ret;
  }

  public virtual cVector3 getDirection() {
    cVector3 ret = new cVector3(cAudioCSharpWrapperPINVOKE.IAudioSource_getDirection(swigCPtr), true);
    return ret;
  }

  public virtual float getRolloffFactor() {
    float ret = cAudioCSharpWrapperPINVOKE.IAudioSource_getRolloffFactor(swigCPtr);
    return ret;
  }

  public virtual float getStrength() {
    float ret = cAudioCSharpWrapperPINVOKE.IAudioSource_getStrength(swigCPtr);
    return ret;
  }

  public virtual float getMinDistance() {
    float ret = cAudioCSharpWrapperPINVOKE.IAudioSource_getMinDistance(swigCPtr);
    return ret;
  }

  public virtual float getMaxDistance() {
    float ret = cAudioCSharpWrapperPINVOKE.IAudioSource_getMaxDistance(swigCPtr);
    return ret;
  }

  public virtual float getPitch() {
    float ret = cAudioCSharpWrapperPINVOKE.IAudioSource_getPitch(swigCPtr);
    return ret;
  }

  public virtual float getVolume() {
    float ret = cAudioCSharpWrapperPINVOKE.IAudioSource_getVolume(swigCPtr);
    return ret;
  }

  public virtual float getMinVolume() {
    float ret = cAudioCSharpWrapperPINVOKE.IAudioSource_getMinVolume(swigCPtr);
    return ret;
  }

  public virtual float getMaxVolume() {
    float ret = cAudioCSharpWrapperPINVOKE.IAudioSource_getMaxVolume(swigCPtr);
    return ret;
  }

  public virtual float getInnerConeAngle() {
    float ret = cAudioCSharpWrapperPINVOKE.IAudioSource_getInnerConeAngle(swigCPtr);
    return ret;
  }

  public virtual float getOuterConeAngle() {
    float ret = cAudioCSharpWrapperPINVOKE.IAudioSource_getOuterConeAngle(swigCPtr);
    return ret;
  }

  public virtual float getOuterConeVolume() {
    float ret = cAudioCSharpWrapperPINVOKE.IAudioSource_getOuterConeVolume(swigCPtr);
    return ret;
  }

  public virtual float getDopplerStrength() {
    float ret = cAudioCSharpWrapperPINVOKE.IAudioSource_getDopplerStrength(swigCPtr);
    return ret;
  }

  public virtual cVector3 getDopplerVelocity() {
    cVector3 ret = new cVector3(cAudioCSharpWrapperPINVOKE.IAudioSource_getDopplerVelocity(swigCPtr), true);
    return ret;
  }

  public virtual void registerEventHandler(ISourceEventHandler handler) {
    cAudioCSharpWrapperPINVOKE.IAudioSource_registerEventHandler(swigCPtr, ISourceEventHandler.getCPtr(handler));
  }

  public virtual void unRegisterEventHandler(ISourceEventHandler handler) {
    cAudioCSharpWrapperPINVOKE.IAudioSource_unRegisterEventHandler(swigCPtr, ISourceEventHandler.getCPtr(handler));
  }

  public virtual void unRegisterAllEventHandlers() {
    cAudioCSharpWrapperPINVOKE.IAudioSource_unRegisterAllEventHandlers(swigCPtr);
  }

}

}
