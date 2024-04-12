bool GLES2DecoderImpl::BoundFramebufferHasDepthAttachment() {
  FramebufferManager::FramebufferInfo* framebuffer =
      GetFramebufferInfoForTarget(GL_DRAW_FRAMEBUFFER_EXT);
  if (framebuffer) {
    return framebuffer->HasDepthAttachment();
  }
  if (offscreen_target_frame_buffer_.get()) {
    return offscreen_target_depth_format_ != 0;
  }
  return back_buffer_has_depth_;
}
