OMX_ERRORTYPE SoftAVC::setNumCores() {
    IV_STATUS_T status;
 ive_ctl_set_num_cores_ip_t s_num_cores_ip;
 ive_ctl_set_num_cores_op_t s_num_cores_op;
    s_num_cores_ip.e_cmd = IVE_CMD_VIDEO_CTL;
    s_num_cores_ip.e_sub_cmd = IVE_CMD_CTL_SET_NUM_CORES;
    s_num_cores_ip.u4_num_cores = MIN(mNumCores, CODEC_MAX_CORES);
    s_num_cores_ip.u4_timestamp_high = -1;
    s_num_cores_ip.u4_timestamp_low = -1;
    s_num_cores_ip.u4_size = sizeof(ive_ctl_set_num_cores_ip_t);

    s_num_cores_op.u4_size = sizeof(ive_ctl_set_num_cores_op_t);

    status = ive_api_function(
            mCodecCtx, (void *) &s_num_cores_ip, (void *) &s_num_cores_op);
 if (status != IV_SUCCESS) {
        ALOGE("Unable to set processor params = 0x%x\n",
                s_num_cores_op.u4_error_code);
 return OMX_ErrorUndefined;
 }
 return OMX_ErrorNone;
}
