status_t ACodec::setCyclicIntraMacroblockRefresh(const sp<AMessage> &msg, int32_t mode) {
    OMX_VIDEO_PARAM_INTRAREFRESHTYPE params;
 InitOMXParams(&params);
    params.nPortIndex = kPortIndexOutput;

    params.eRefreshMode = static_cast<OMX_VIDEO_INTRAREFRESHTYPE>(mode);

 if (params.eRefreshMode == OMX_VIDEO_IntraRefreshCyclic ||
            params.eRefreshMode == OMX_VIDEO_IntraRefreshBoth) {
 int32_t mbs;
 if (!msg->findInt32("intra-refresh-CIR-mbs", &mbs)) {
 return INVALID_OPERATION;
 }
        params.nCirMBs = mbs;
 }

 if (params.eRefreshMode == OMX_VIDEO_IntraRefreshAdaptive ||
            params.eRefreshMode == OMX_VIDEO_IntraRefreshBoth) {
 int32_t mbs;
 if (!msg->findInt32("intra-refresh-AIR-mbs", &mbs)) {
 return INVALID_OPERATION;
 }
        params.nAirMBs = mbs;

 int32_t ref;
 if (!msg->findInt32("intra-refresh-AIR-ref", &ref)) {
 return INVALID_OPERATION;
 }
        params.nAirRef = ref;
 }

 status_t err = mOMX->setParameter(
            mNode, OMX_IndexParamVideoIntraRefresh,
 &params, sizeof(params));
 return err;
}
