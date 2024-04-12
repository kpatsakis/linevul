void WebContentsImpl::FullscreenFrameSetUpdated() {
  if (fullscreen_frames_.empty()) {
    current_fullscreen_frame_ = nullptr;
    return;
  }

  RenderFrameHostImpl* new_fullscreen_frame = *std::max_element(
      fullscreen_frames_.begin(), fullscreen_frames_.end(), FrameCompareDepth);

  if (new_fullscreen_frame == current_fullscreen_frame_)
    return;
  current_fullscreen_frame_ = new_fullscreen_frame;

  for (auto& observer : observers_)
    observer.DidAcquireFullscreen(new_fullscreen_frame);

  if (display_cutout_host_impl_)
    display_cutout_host_impl_->DidAcquireFullscreen(new_fullscreen_frame);
}
