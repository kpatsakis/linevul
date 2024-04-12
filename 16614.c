static vpx_codec_err_t update_error_state(vpx_codec_alg_priv_t *ctx,
 const struct vpx_internal_error_info *error) {
 if (error->error_code)
    set_error_detail(ctx, error->has_detail ? error->detail : NULL);

 return error->error_code;
}
