bool WebMediaPlayerImpl::CopyVideoTextureToPlatformTexture(
    gpu::gles2::GLES2Interface* gl,
    unsigned int target,
    unsigned int texture,
    unsigned internal_format,
    unsigned format,
    unsigned type,
    int level,
    bool premultiply_alpha,
    bool flip_y,
    int already_uploaded_id,
    VideoFrameUploadMetadata* out_metadata) {
  DCHECK(main_task_runner_->BelongsToCurrentThread());
  TRACE_EVENT0("media", "WebMediaPlayerImpl:copyVideoTextureToPlatformTexture");

  if (cdm_context_ref_)
    return false;

  scoped_refptr<VideoFrame> video_frame = GetCurrentFrameFromCompositor();
  if (!video_frame.get() || !video_frame->HasTextures()) {
    return false;
  }
  if (out_metadata) {
    ComputeFrameUploadMetadata(video_frame.get(), already_uploaded_id,
                               out_metadata);
    if (out_metadata->skipped) {
      return true;
    }
  }

  Context3D context_3d;
  if (context_provider_) {
    context_3d = Context3D(context_provider_->ContextGL(),
                           context_provider_->GrContext());
  }
  return video_renderer_.CopyVideoFrameTexturesToGLTexture(
      context_3d, gl, video_frame.get(), target, texture, internal_format,
      format, type, level, premultiply_alpha, flip_y);
}
