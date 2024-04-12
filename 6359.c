static vpx_codec_err_t vp8_get_last_ref_frame(vpx_codec_alg_priv_t *ctx,
                                              va_list args)
{
 int *ref_info = va_arg(args, int *);

 if (ref_info && !ctx->yv12_frame_buffers.use_frame_threads)
 {
        VP8D_COMP *pbi = (VP8D_COMP *)ctx->yv12_frame_buffers.pbi[0];
        VP8_COMMON *oci = &pbi->common;
 *ref_info =
 (vp8dx_references_buffer( oci, ALTREF_FRAME )?VP8_ALTR_FRAME:0) |
 (vp8dx_references_buffer( oci, GOLDEN_FRAME )?VP8_GOLD_FRAME:0) |
 (vp8dx_references_buffer( oci, LAST_FRAME )?VP8_LAST_FRAME:0);

 return VPX_CODEC_OK;
 }
 else
 return VPX_CODEC_INVALID_PARAM;
}
