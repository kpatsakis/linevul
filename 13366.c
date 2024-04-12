static void set_error_detail(vpx_codec_alg_priv_t *ctx,
 const char *const error) {
  ctx->base.err_detail = error;
}
