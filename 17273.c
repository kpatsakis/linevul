WORD32 ihevcd_get_sei_mastering_params(iv_obj_t *ps_codec_obj,
 void *pv_api_ip,
 void *pv_api_op)
{
 ihevcd_cxa_ctl_get_sei_mastering_params_ip_t *ps_ip;
 ihevcd_cxa_ctl_get_sei_mastering_params_op_t *ps_op;
 codec_t *ps_codec = (codec_t *)ps_codec_obj->pv_codec_handle;
 sei_params_t *ps_sei;
 mastering_dis_col_vol_sei_params_t *ps_mastering_dis_col_vol;
    WORD32 i;

    ps_ip = (ihevcd_cxa_ctl_get_sei_mastering_params_ip_t *)pv_api_ip;
    ps_op = (ihevcd_cxa_ctl_get_sei_mastering_params_op_t *)pv_api_op;
    UNUSED(ps_ip);
 if(NULL == ps_codec->ps_disp_buf)
 {
        ps_op->u4_error_code = IHEVCD_SEI_MASTERING_PARAMS_NOT_FOUND;
 return IV_FAIL;
 }
    ps_sei = &ps_codec->ps_disp_buf->s_sei_params;
 if((0 == ps_sei->i4_sei_mastering_disp_colour_vol_params_present_flags)
 || (0 == ps_sei->i1_sei_parameters_present_flag))
 {
        ps_op->u4_error_code = IHEVCD_SEI_MASTERING_PARAMS_NOT_FOUND;
 return IV_FAIL;
 }

    ps_mastering_dis_col_vol = &ps_sei->s_mastering_dis_col_vol_sei_params;

 for(i = 0; i < 3; i++)
 {
        ps_op->au2_display_primaries_x[i] =
                    ps_mastering_dis_col_vol->au2_display_primaries_x[i];

        ps_op->au2_display_primaries_y[i] =
                    ps_mastering_dis_col_vol->au2_display_primaries_y[i];
 }

    ps_op->u2_white_point_x = ps_mastering_dis_col_vol->u2_white_point_x;

    ps_op->u2_white_point_y = ps_mastering_dis_col_vol->u2_white_point_y;

    ps_op->u4_max_display_mastering_luminance =
                    ps_mastering_dis_col_vol->u4_max_display_mastering_luminance;

    ps_op->u4_min_display_mastering_luminance =
                    ps_mastering_dis_col_vol->u4_min_display_mastering_luminance;

 return IV_SUCCESS;
}
