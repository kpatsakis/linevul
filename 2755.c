WORD32 ih264d_get_buf_info(iv_obj_t *dec_hdl, void *pv_api_ip, void *pv_api_op)
{

 dec_struct_t * ps_dec;
    UWORD8 i = 0; // Default for 420P format
    UWORD16 pic_wd, pic_ht;
 ivd_ctl_getbufinfo_op_t *ps_ctl_op =
 (ivd_ctl_getbufinfo_op_t*)pv_api_op;
    UNUSED(pv_api_ip);
    ps_ctl_op->u4_error_code = 0;

    ps_dec = (dec_struct_t *)(dec_hdl->pv_codec_handle);

    ps_ctl_op->u4_min_num_in_bufs = MIN_IN_BUFS;
 if(ps_dec->u1_chroma_format == IV_YUV_420P)
        ps_ctl_op->u4_min_num_out_bufs = MIN_OUT_BUFS_420;
 else if(ps_dec->u1_chroma_format == IV_YUV_422ILE)
        ps_ctl_op->u4_min_num_out_bufs = MIN_OUT_BUFS_422ILE;
 else if(ps_dec->u1_chroma_format == IV_RGB_565)
        ps_ctl_op->u4_min_num_out_bufs = MIN_OUT_BUFS_RGB565;
 else if((ps_dec->u1_chroma_format == IV_YUV_420SP_UV)
 || (ps_dec->u1_chroma_format == IV_YUV_420SP_VU))
        ps_ctl_op->u4_min_num_out_bufs = MIN_OUT_BUFS_420SP;

 else
 {
 return IV_FAIL;
 }

    ps_ctl_op->u4_num_disp_bufs = 1;


    pic_wd = 0;
    pic_ht = 0;

 if(ps_dec->i4_header_decoded == 3)
 {

 if(0 == ps_dec->u4_share_disp_buf)
 {
            pic_wd = ps_dec->u2_disp_width;
            pic_ht = ps_dec->u2_disp_height;

 }
 else
 {
            pic_wd = ps_dec->u2_frm_wd_y;
            pic_ht = ps_dec->u2_frm_ht_y;
 }

 }

 for(i = 0; i < ps_ctl_op->u4_min_num_in_bufs; i++)
 {
        ps_ctl_op->u4_min_in_buf_size[i] = MAX(256000, pic_wd * pic_ht * 3 / 2);
 }
 if((WORD32)ps_dec->u4_app_disp_width > pic_wd)
        pic_wd = ps_dec->u4_app_disp_width;

 if(0 == ps_dec->u4_share_disp_buf)
        ps_ctl_op->u4_num_disp_bufs = 1;
 else
 {
 if((NULL != ps_dec->ps_cur_sps) && (1 == (ps_dec->ps_cur_sps->u1_is_valid)))
 {
 if((ps_dec->ps_cur_sps->u1_vui_parameters_present_flag == 1) &&
 (1 == ps_dec->ps_cur_sps->s_vui.u1_bitstream_restriction_flag))
 {
                ps_ctl_op->u4_num_disp_bufs =
                                ps_dec->ps_cur_sps->s_vui.u4_num_reorder_frames + 1;
 }
 else
 {
 /*if VUI is not present assume maximum possible refrence frames for the level,
                 * as max reorder frames*/
                ps_ctl_op->u4_num_disp_bufs = ih264d_get_dpb_size(ps_dec->ps_cur_sps);
 }

            ps_ctl_op->u4_num_disp_bufs +=
                            ps_dec->ps_cur_sps->u1_num_ref_frames + 1;

 }
 else
 {
            ps_ctl_op->u4_num_disp_bufs = 32;

 }

        ps_ctl_op->u4_num_disp_bufs = MAX(
                        ps_ctl_op->u4_num_disp_bufs, 6);
        ps_ctl_op->u4_num_disp_bufs = MIN(
                        ps_ctl_op->u4_num_disp_bufs, 32);
 }

 /*!*/
 if(ps_dec->u1_chroma_format == IV_YUV_420P)
 {
        ps_ctl_op->u4_min_out_buf_size[0] = (pic_wd * pic_ht);
        ps_ctl_op->u4_min_out_buf_size[1] = (pic_wd * pic_ht)
 >> 2;
        ps_ctl_op->u4_min_out_buf_size[2] = (pic_wd * pic_ht)
 >> 2;
 }
 else if(ps_dec->u1_chroma_format == IV_YUV_422ILE)
 {
        ps_ctl_op->u4_min_out_buf_size[0] = (pic_wd * pic_ht)
 * 2;
        ps_ctl_op->u4_min_out_buf_size[1] =
                        ps_ctl_op->u4_min_out_buf_size[2] = 0;
 }
 else if(ps_dec->u1_chroma_format == IV_RGB_565)
 {
        ps_ctl_op->u4_min_out_buf_size[0] = (pic_wd * pic_ht)
 * 2;
        ps_ctl_op->u4_min_out_buf_size[1] =
                        ps_ctl_op->u4_min_out_buf_size[2] = 0;
 }
 else if((ps_dec->u1_chroma_format == IV_YUV_420SP_UV)
 || (ps_dec->u1_chroma_format == IV_YUV_420SP_VU))
 {
        ps_ctl_op->u4_min_out_buf_size[0] = (pic_wd * pic_ht);
        ps_ctl_op->u4_min_out_buf_size[1] = (pic_wd * pic_ht)
 >> 1;
        ps_ctl_op->u4_min_out_buf_size[2] = 0;
 }
    ps_dec->u4_num_disp_bufs_requested = ps_ctl_op->u4_num_disp_bufs;

 return IV_SUCCESS;
}
