static void set_ppflags(const vpx_codec_alg_priv_t *ctx,
 vp9_ppflags_t *flags) {
  flags->post_proc_flag =
      ctx->postproc_cfg.post_proc_flag;

  flags->deblocking_level = ctx->postproc_cfg.deblocking_level;
  flags->noise_level = ctx->postproc_cfg.noise_level;
}
