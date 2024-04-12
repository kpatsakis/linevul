void WebMediaPlayerImpl::SuspendForRemote() {
  video_decode_stats_reporter_.reset();

  if (pipeline_controller_.IsPipelineSuspended() &&
      !IsNewRemotePlaybackPipelineEnabled()) {
    scoped_refptr<VideoFrame> frame = cast_impl_.GetCastingBanner();
    if (frame)
      compositor_->PaintSingleFrame(frame);
  }

  UpdatePlayState();
}
