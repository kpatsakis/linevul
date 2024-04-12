WORD32 ih264d_set_flush_mode(iv_obj_t *dec_hdl, void *pv_api_ip, void *pv_api_op)
{
 dec_struct_t * ps_dec;
 ivd_ctl_flush_op_t *ps_ctl_op = (ivd_ctl_flush_op_t*)pv_api_op;
    ps_ctl_op->u4_error_code = 0;

    ps_dec = (dec_struct_t *)(dec_hdl->pv_codec_handle);
    UNUSED(pv_api_ip);
 /* ! */
 /* Signal flush frame control call */
    ps_dec->u1_flushfrm = 1;

 if(ps_dec->u1_init_dec_flag == 1)
 {
        ih264d_release_pics_in_dpb((void *)ps_dec, ps_dec->u1_pic_bufs);
        ih264d_release_display_bufs(ps_dec);
 }

    ps_ctl_op->u4_error_code = 0;

 return IV_SUCCESS;
}
