OMX_ERRORTYPE  omx_video::get_extension_index(OMX_IN OMX_HANDLETYPE      hComp,
        OMX_IN OMX_STRING      paramName,
        OMX_OUT OMX_INDEXTYPE* indexType)
{
 (void)hComp;
 if (m_state == OMX_StateInvalid) {
        DEBUG_PRINT_ERROR("ERROR: Get Extension Index in Invalid State");
 return OMX_ErrorInvalidState;
 }
#ifdef MAX_RES_1080P
 if (!strncmp(paramName, "OMX.QCOM.index.param.SliceDeliveryMode",
 sizeof("OMX.QCOM.index.param.SliceDeliveryMode") - 1)) {
 *indexType = (OMX_INDEXTYPE)OMX_QcomIndexEnableSliceDeliveryMode;
 return OMX_ErrorNone;
 }
#endif
#ifdef _ANDROID_ICS_
 if (!strncmp(paramName, "OMX.google.android.index.storeMetaDataInBuffers",
 sizeof("OMX.google.android.index.storeMetaDataInBuffers") - 1)) {
 *indexType = (OMX_INDEXTYPE)OMX_QcomIndexParamVideoMetaBufferMode;
 return OMX_ErrorNone;
 }
#endif
 if (!strncmp(paramName, "OMX.google.android.index.prependSPSPPSToIDRFrames",
 sizeof("OMX.google.android.index.prependSPSPPSToIDRFrames") - 1)) {
 *indexType = (OMX_INDEXTYPE)OMX_QcomIndexParamSequenceHeaderWithIDR;
 return OMX_ErrorNone;
 }
 return OMX_ErrorNotImplemented;
}
