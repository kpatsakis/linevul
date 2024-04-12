SoftAACEncoder2::SoftAACEncoder2(
 const char *name,
 const OMX_CALLBACKTYPE *callbacks,
        OMX_PTR appData,
        OMX_COMPONENTTYPE **component)
 : SimpleSoftOMXComponent(name, callbacks, appData, component),
      mAACEncoder(NULL),
      mNumChannels(1),
      mSampleRate(44100),
      mBitRate(0),
      mSBRMode(-1),
      mSBRRatio(0),
      mAACProfile(OMX_AUDIO_AACObjectLC),
      mSentCodecSpecificData(false),
      mInputSize(0),
      mInputFrame(NULL),
      mInputTimeUs(-1ll),
      mSawInputEOS(false),
      mSignalledError(false) {
    initPorts();
    CHECK_EQ(initEncoder(), (status_t)OK);
    setAudioParams();
}
