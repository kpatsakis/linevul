OMX_ERRORTYPE SoftAVC::setDimensions() {
 ive_ctl_set_dimensions_ip_t s_dimensions_ip;
 ive_ctl_set_dimensions_op_t s_dimensions_op;
    IV_STATUS_T status;

    s_dimensions_ip.e_cmd = IVE_CMD_VIDEO_CTL;
    s_dimensions_ip.e_sub_cmd = IVE_CMD_CTL_SET_DIMENSIONS;
    s_dimensions_ip.u4_ht = mHeight;
    s_dimensions_ip.u4_wd = mWidth;

    s_dimensions_ip.u4_timestamp_high = -1;
    s_dimensions_ip.u4_timestamp_low = -1;

    s_dimensions_ip.u4_size = sizeof(ive_ctl_set_dimensions_ip_t);
    s_dimensions_op.u4_size = sizeof(ive_ctl_set_dimensions_op_t);

    status = ive_api_function(mCodecCtx, &s_dimensions_ip, &s_dimensions_op);
 if (status != IV_SUCCESS) {
        ALOGE("Unable to set frame dimensions = 0x%x\n",
                s_dimensions_op.u4_error_code);
 return OMX_ErrorUndefined;
 }
 return OMX_ErrorNone;
}
