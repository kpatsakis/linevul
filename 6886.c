OMX_ERRORTYPE SoftVPXEncoder::internalSetVp8Params(
 const OMX_VIDEO_PARAM_VP8TYPE* vp8Params) {
 if (vp8Params->nPortIndex != kOutputPortIndex) {
 return OMX_ErrorUnsupportedIndex;
 }

 if (vp8Params->eProfile != OMX_VIDEO_VP8ProfileMain) {
 return OMX_ErrorBadParameter;
 }

 if (vp8Params->eLevel == OMX_VIDEO_VP8Level_Version0 ||
        vp8Params->eLevel == OMX_VIDEO_VP8Level_Version1 ||
        vp8Params->eLevel == OMX_VIDEO_VP8Level_Version2 ||
        vp8Params->eLevel == OMX_VIDEO_VP8Level_Version3) {
        mLevel = vp8Params->eLevel;
 } else {
 return OMX_ErrorBadParameter;
 }

 if (vp8Params->nDCTPartitions <= kMaxDCTPartitions) {
        mDCTPartitions = vp8Params->nDCTPartitions;
 } else {
 return OMX_ErrorBadParameter;
 }

    mErrorResilience = vp8Params->bErrorResilientMode;
 return OMX_ErrorNone;
}
