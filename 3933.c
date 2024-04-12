static INLINE void check_resync(vpx_codec_alg_priv_t *const ctx,
 const VP9Decoder *const pbi) {
 if (ctx->need_resync == 1 && pbi->need_resync == 0 &&
 (pbi->common.intra_only || pbi->common.frame_type == KEY_FRAME))
    ctx->need_resync = 0;
}
