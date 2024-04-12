void RenderFrameImpl::FrameRectsChanged(const blink::WebRect& frame_rect) {
  gfx::Size frame_size(frame_rect.width, frame_rect.height);
  if (!frame_size_ || *frame_size_ != frame_size) {
    frame_size_ = frame_size;
    GetFrameHost()->FrameSizeChanged(frame_size);
  }
}
