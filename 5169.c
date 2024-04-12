WORD32 ih264d_ctl(iv_obj_t *dec_hdl, void *pv_api_ip, void *pv_api_op)
{
 ivd_ctl_set_config_ip_t *ps_ctl_ip;
 ivd_ctl_set_config_op_t *ps_ctl_op;
    WORD32 ret = IV_SUCCESS;
    UWORD32 subcommand;
 dec_struct_t *ps_dec = dec_hdl->pv_codec_handle;

 if(ps_dec->init_done != 1)
 {
 return IV_FAIL;
 }
    ps_ctl_ip = (ivd_ctl_set_config_ip_t*)pv_api_ip;
    ps_ctl_op = (ivd_ctl_set_config_op_t*)pv_api_op;
    ps_ctl_op->u4_error_code = 0;
    subcommand = ps_ctl_ip->e_sub_cmd;

 switch(subcommand)
 {
 case IVD_CMD_CTL_GETPARAMS:
            ret = ih264d_get_status(dec_hdl, (void *)pv_api_ip,
 (void *)pv_api_op);
 break;
 case IVD_CMD_CTL_SETPARAMS:
            ret = ih264d_set_params(dec_hdl, (void *)pv_api_ip,
 (void *)pv_api_op);
 break;
 case IVD_CMD_CTL_RESET:
            ret = ih264d_reset(dec_hdl, (void *)pv_api_ip, (void *)pv_api_op);
 break;
 case IVD_CMD_CTL_SETDEFAULT:
            ret = ih264d_set_default_params(dec_hdl, (void *)pv_api_ip,
 (void *)pv_api_op);
 break;
 case IVD_CMD_CTL_FLUSH:
            ret = ih264d_set_flush_mode(dec_hdl, (void *)pv_api_ip,
 (void *)pv_api_op);
 break;
 case IVD_CMD_CTL_GETBUFINFO:
            ret = ih264d_get_buf_info(dec_hdl, (void *)pv_api_ip,
 (void *)pv_api_op);
 break;
 case IVD_CMD_CTL_GETVERSION:
            ret = ih264d_get_version(dec_hdl, (void *)pv_api_ip,
 (void *)pv_api_op);
 break;
 case IH264D_CMD_CTL_DEGRADE:
            ret = ih264d_set_degrade(dec_hdl, (void *)pv_api_ip,
 (void *)pv_api_op);
 break;

 case IH264D_CMD_CTL_SET_NUM_CORES:
            ret = ih264d_set_num_cores(dec_hdl, (void *)pv_api_ip,
 (void *)pv_api_op);
 break;
 case IH264D_CMD_CTL_GET_BUFFER_DIMENSIONS:
            ret = ih264d_get_frame_dimensions(dec_hdl, (void *)pv_api_ip,
 (void *)pv_api_op);
 break;
 case IH264D_CMD_CTL_GET_VUI_PARAMS:
            ret = ih264d_get_vui_params(dec_hdl, (void *)pv_api_ip,
 (void *)pv_api_op);
 break;

 case IH264D_CMD_CTL_SET_PROCESSOR:
            ret = ih264d_set_processor(dec_hdl, (void *)pv_api_ip,
 (void *)pv_api_op);
 break;
 default:
            H264_DEC_DEBUG_PRINT("\ndo nothing\n")
 ;
 break;
 }

 return ret;
}
