static vpx_codec_err_t vp8_get_last_ref_updates(vpx_codec_alg_priv_t *ctx,
                                                va_list args)
{
 int *update_info = va_arg(args, int *);

 if (update_info && !ctx->yv12_frame_buffers.use_frame_threads)
 {
        VP8D_COMP *pbi = (VP8D_COMP *)ctx->yv12_frame_buffers.pbi[0];

 *update_info = pbi->common.refresh_alt_ref_frame * (int) VP8_ALTR_FRAME
 + pbi->common.refresh_golden_frame * (int) VP8_GOLD_FRAME
 + pbi->common.refresh_last_frame * (int) VP8_LAST_FRAME;

 return VPX_CODEC_OK;
 }
 else
 return VPX_CODEC_INVALID_PARAM;
}
