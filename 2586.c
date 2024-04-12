static vpx_codec_err_t ctrl_set_reference(vpx_codec_alg_priv_t *ctx,
                                          va_list args) {
 vpx_ref_frame_t *const data = va_arg(args, vpx_ref_frame_t *);

 if (ctx->frame_parallel_decode) {
    set_error_detail(ctx, "Not supported in frame parallel decode");
 return VPX_CODEC_INCAPABLE;
 }

 if (data) {
 vpx_ref_frame_t *const frame = (vpx_ref_frame_t *)data;
    YV12_BUFFER_CONFIG sd;
 VPxWorker *const worker = ctx->frame_workers;
 FrameWorkerData *const frame_worker_data = (FrameWorkerData *)worker->data1;
    image2yuvconfig(&frame->img, &sd);
 return vp9_set_reference_dec(&frame_worker_data->pbi->common,
 (VP9_REFFRAME)frame->frame_type, &sd);
 } else {
 return VPX_CODEC_INVALID_PARAM;
 }
}
