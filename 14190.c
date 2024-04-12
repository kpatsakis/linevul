SoftMPEG4Encoder::SoftMPEG4Encoder(
 const char *name,
 const OMX_CALLBACKTYPE *callbacks,
            OMX_PTR appData,
            OMX_COMPONENTTYPE **component)
 : SoftVideoEncoderOMXComponent(name, callbacks, appData, component),
      mEncodeMode(COMBINE_MODE_WITH_ERR_RES),
      mVideoWidth(176),
      mVideoHeight(144),
      mVideoFrameRate(30),
      mVideoBitRate(192000),
      mVideoColorFormat(OMX_COLOR_FormatYUV420Planar),
      mStoreMetaDataInBuffers(false),
      mIDRFrameRefreshIntervalInSec(1),
      mNumInputFrames(-1),
      mStarted(false),
      mSawInputEOS(false),
      mSignalledError(false),
      mHandle(new tagvideoEncControls),
      mEncParams(new tagvideoEncOptions),
      mInputFrameData(NULL) {

 if (!strcmp(name, "OMX.google.h263.encoder")) {
        mEncodeMode = H263_MODE;
 } else {
        CHECK(!strcmp(name, "OMX.google.mpeg4.encoder"));
 }

    initPorts();
    ALOGI("Construct SoftMPEG4Encoder");
}
