void omx_vdec::append_user_extradata(OMX_OTHER_EXTRADATATYPE *extra,
            OMX_OTHER_EXTRADATATYPE *p_user)
{
 int userdata_size = 0;
 struct msm_vidc_stream_userdata_payload *userdata_payload = NULL;
    userdata_payload =
 (struct msm_vidc_stream_userdata_payload *)(void *)p_user->data;
    userdata_size = p_user->nDataSize;
    extra->nSize = OMX_USERDATA_EXTRADATA_SIZE + userdata_size;
    extra->nVersion.nVersion = OMX_SPEC_VERSION;
    extra->nPortIndex = OMX_CORE_OUTPUT_PORT_INDEX;
    extra->eType = (OMX_EXTRADATATYPE)OMX_ExtraDataMP2UserData;
    extra->nDataSize = userdata_size;
 if (extra->data && p_user->data && extra->nDataSize)
        memcpy(extra->data, p_user->data, extra->nDataSize);
    print_debug_extradata(extra);
}
