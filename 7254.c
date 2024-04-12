static vpx_codec_err_t vp8_get_frame_corrupted(vpx_codec_alg_priv_t *ctx,
                                               va_list args)
{

 int *corrupted = va_arg(args, int *);
    VP8D_COMP *pbi = (VP8D_COMP *)ctx->yv12_frame_buffers.pbi[0];

 if (corrupted && pbi)
 {
 const YV12_BUFFER_CONFIG *const frame = pbi->common.frame_to_show;
 if (frame == NULL) return VPX_CODEC_ERROR;
 *corrupted = frame->corrupted;
 return VPX_CODEC_OK;
 }
 else
 return VPX_CODEC_INVALID_PARAM;

}
