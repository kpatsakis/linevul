WORD32 ihevcd_ctl(iv_obj_t *ps_codec_obj, void *pv_api_ip, void *pv_api_op)
{
 ivd_ctl_set_config_ip_t *ps_ctl_ip;
 ivd_ctl_set_config_op_t *ps_ctl_op;
    WORD32 ret = 0;
    WORD32 subcommand;
 codec_t *ps_codec = (codec_t *)ps_codec_obj->pv_codec_handle;

    ps_ctl_ip = (ivd_ctl_set_config_ip_t *)pv_api_ip;
    ps_ctl_op = (ivd_ctl_set_config_op_t *)pv_api_op;

 if(ps_codec->i4_init_done != 1)
 {
        ps_ctl_op->u4_error_code |= 1 << IVD_FATALERROR;
        ps_ctl_op->u4_error_code |= IHEVCD_INIT_NOT_DONE;
 return IV_FAIL;
 }
    subcommand = ps_ctl_ip->e_sub_cmd;

 switch(subcommand)
 {
 case IVD_CMD_CTL_GETPARAMS:
            ret = ihevcd_get_status(ps_codec_obj, (void *)pv_api_ip,
 (void *)pv_api_op);
 break;
 case IVD_CMD_CTL_SETPARAMS:
            ret = ihevcd_set_params(ps_codec_obj, (void *)pv_api_ip,
 (void *)pv_api_op);
 break;
 case IVD_CMD_CTL_RESET:
            ret = ihevcd_reset(ps_codec_obj, (void *)pv_api_ip,
 (void *)pv_api_op);
 break;
 case IVD_CMD_CTL_SETDEFAULT:
 {
 ivd_ctl_set_config_op_t *s_ctl_dynparams_op =
 (ivd_ctl_set_config_op_t *)pv_api_op;

            ret = ihevcd_set_default_params(ps_codec);
 if(IV_SUCCESS == ret)
                s_ctl_dynparams_op->u4_error_code = 0;
 break;
 }
 case IVD_CMD_CTL_FLUSH:
            ret = ihevcd_set_flush_mode(ps_codec_obj, (void *)pv_api_ip,
 (void *)pv_api_op);
 break;
 case IVD_CMD_CTL_GETBUFINFO:
            ret = ihevcd_get_buf_info(ps_codec_obj, (void *)pv_api_ip,
 (void *)pv_api_op);
 break;
 case IVD_CMD_CTL_GETVERSION:
 {
 ivd_ctl_getversioninfo_ip_t *ps_ip;
 ivd_ctl_getversioninfo_op_t *ps_op;
            IV_API_CALL_STATUS_T ret;
            ps_ip = (ivd_ctl_getversioninfo_ip_t *)pv_api_ip;
            ps_op = (ivd_ctl_getversioninfo_op_t *)pv_api_op;

            ps_op->u4_error_code = IV_SUCCESS;

 if((WORD32)ps_ip->u4_version_buffer_size <= 0)
 {
                ps_op->u4_error_code = IHEVCD_CXA_VERS_BUF_INSUFFICIENT;
                ret = IV_FAIL;
 }
 else
 {
                ret = ihevcd_get_version((CHAR *)ps_ip->pv_version_buffer,
                                         ps_ip->u4_version_buffer_size);
 if(ret != IV_SUCCESS)
 {
                    ps_op->u4_error_code = IHEVCD_CXA_VERS_BUF_INSUFFICIENT;
                    ret = IV_FAIL;
 }
 }
 }
 break;
 case IHEVCD_CXA_CMD_CTL_DEGRADE:
            ret = ihevcd_set_degrade(ps_codec_obj, (void *)pv_api_ip,
 (void *)pv_api_op);
 break;
 case IHEVCD_CXA_CMD_CTL_SET_NUM_CORES:
            ret = ihevcd_set_num_cores(ps_codec_obj, (void *)pv_api_ip,
 (void *)pv_api_op);
 break;
 case IHEVCD_CXA_CMD_CTL_GET_BUFFER_DIMENSIONS:
            ret = ihevcd_get_frame_dimensions(ps_codec_obj, (void *)pv_api_ip,
 (void *)pv_api_op);
 break;
 case IHEVCD_CXA_CMD_CTL_GET_VUI_PARAMS:
            ret = ihevcd_get_vui_params(ps_codec_obj, (void *)pv_api_ip,
 (void *)pv_api_op);
 break;
 case IHEVCD_CXA_CMD_CTL_GET_SEI_MASTERING_PARAMS:
            ret = ihevcd_get_sei_mastering_params(ps_codec_obj, (void *)pv_api_ip,
 (void *)pv_api_op);
 break;
 case IHEVCD_CXA_CMD_CTL_SET_PROCESSOR:
            ret = ihevcd_set_processor(ps_codec_obj, (void *)pv_api_ip,
 (void *)pv_api_op);
 break;
 default:
            DEBUG("\nDo nothing\n");
 break;
 }

 return ret;
}
