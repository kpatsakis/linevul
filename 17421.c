AudioFlinger::EffectChain::EffectChain(ThreadBase *thread,
 int sessionId)
 : mThread(thread), mSessionId(sessionId), mActiveTrackCnt(0), mTrackCnt(0), mTailBufferCount(0),
      mOwnInBuffer(false), mVolumeCtrlIdx(-1), mLeftVolume(UINT_MAX), mRightVolume(UINT_MAX),
      mNewLeftVolume(UINT_MAX), mNewRightVolume(UINT_MAX), mForceVolume(false)
{
    mStrategy = AudioSystem::getStrategyForStream(AUDIO_STREAM_MUSIC);
 if (thread == NULL) {
 return;
 }
    mMaxTailBuffers = ((kProcessTailDurationMs * thread->sampleRate()) / 1000) /
                                    thread->frameCount();
}
