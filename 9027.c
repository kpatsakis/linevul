bool LocalFrameClientImpl::ShouldBlockWebGL() {
  DCHECK(web_frame_->Client());
  return web_frame_->Client()->ShouldBlockWebGL();
}
