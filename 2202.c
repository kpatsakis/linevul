SoftAMRNBEncoder::SoftAMRNBEncoder(
 const char *name,
 const OMX_CALLBACKTYPE *callbacks,
        OMX_PTR appData,
        OMX_COMPONENTTYPE **component)
 : SimpleSoftOMXComponent(name, callbacks, appData, component),
      mEncState(NULL),
      mSidState(NULL),
      mBitRate(0),
      mMode(MR475),
      mInputSize(0),
      mInputTimeUs(-1ll),
      mSawInputEOS(false),
      mSignalledError(false) {
    initPorts();
    CHECK_EQ(initEncoder(), (status_t)OK);
}
