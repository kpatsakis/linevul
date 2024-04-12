static void release_last_output_frame(vpx_codec_alg_priv_t *ctx) {
 RefCntBuffer *const frame_bufs = ctx->buffer_pool->frame_bufs;
 if (ctx->frame_parallel_decode && ctx->last_show_frame >= 0) {
 BufferPool *const pool = ctx->buffer_pool;
    lock_buffer_pool(pool);
    decrease_ref_count(ctx->last_show_frame, frame_bufs, pool);
    unlock_buffer_pool(pool);
 }
}
