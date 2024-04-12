void WebMediaPlayerImpl::OnPipelineSuspended() {
#if defined(OS_ANDROID)
  if (IsRemote() && !IsNewRemotePlaybackPipelineEnabled()) {
    scoped_refptr<VideoFrame> frame = cast_impl_.GetCastingBanner();
    if (frame)
      compositor_->PaintSingleFrame(frame);
  }
#endif

  if (data_source_)
    data_source_->OnBufferingHaveEnough(true);

  ReportMemoryUsage();

  if (pending_suspend_resume_cycle_) {
    pending_suspend_resume_cycle_ = false;
    UpdatePlayState();
  }
}
