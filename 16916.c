WORD32 ihevcd_get_total_pic_buf_size(codec_t *ps_codec,
                                     WORD32 wd,
                                     WORD32 ht)
{
    WORD32 size;
    WORD32 num_luma_samples;
    WORD32 max_dpb_size;
    WORD32 num_samples;


 sps_t *ps_sps = (ps_codec->s_parse.ps_sps_base + ps_codec->i4_sps_id);

 /* Get maximum number of buffers for the current picture size */
    max_dpb_size = ps_sps->ai1_sps_max_dec_pic_buffering[ps_sps->i1_sps_max_sub_layers - 1];

 if(ps_codec->e_frm_out_mode != IVD_DECODE_FRAME_OUT)
        max_dpb_size += ps_sps->ai1_sps_max_num_reorder_pics[ps_sps->i1_sps_max_sub_layers - 1];

    max_dpb_size++;
 /* Allocation is required for
     * (Wd + horz_pad) * (Ht + vert_pad) * (2 * max_dpb_size + 1)
     */

 /* Account for padding area */
    num_luma_samples = (wd + PAD_WD) * (ht + PAD_HT);

 /* Account for chroma */
    num_samples = num_luma_samples * 3 / 2;

 /* Number of bytes in reference pictures */
    size = num_samples * max_dpb_size;


 return size;
}
