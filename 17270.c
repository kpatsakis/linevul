void WebMediaPlayerImpl::Paint(cc::PaintCanvas* canvas,
                               const blink::WebRect& rect,
                               cc::PaintFlags& flags,
                               int already_uploaded_id,
                               VideoFrameUploadMetadata* out_metadata) {
  DCHECK(main_task_runner_->BelongsToCurrentThread());
  TRACE_EVENT0("media", "WebMediaPlayerImpl:paint");

  if (cdm_context_ref_)
    return;

  scoped_refptr<VideoFrame> video_frame = GetCurrentFrameFromCompositor();

  gfx::Rect gfx_rect(rect);
  Context3D context_3d;
  if (video_frame.get() && video_frame->HasTextures()) {
    if (context_provider_) {
      context_3d = Context3D(context_provider_->ContextGL(),
                             context_provider_->GrContext());
    }
    if (!context_3d.gl)
      return;  // Unable to get/create a shared main thread context.
    if (!context_3d.gr_context)
      return;  // The context has been lost since and can't setup a GrContext.
  }
  if (out_metadata && video_frame) {
    ComputeFrameUploadMetadata(video_frame.get(), already_uploaded_id,
                               out_metadata);
    if (out_metadata->skipped) {
      return;
    }
  }
  video_renderer_.Paint(
      video_frame, canvas, gfx::RectF(gfx_rect), flags,
      pipeline_metadata_.video_decoder_config.video_rotation(), context_3d);
}
