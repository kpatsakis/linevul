bool GLES2DecoderImpl::FormsTextureCopyingFeedbackLoop(
    TextureRef* texture, GLint level) {
  Framebuffer* framebuffer = features().chromium_framebuffer_multisample ?
      framebuffer_state_.bound_read_framebuffer.get() :
      framebuffer_state_.bound_draw_framebuffer.get();
  if (!framebuffer)
    return false;
  const Framebuffer::Attachment* attachment = framebuffer->GetAttachment(
      GL_COLOR_ATTACHMENT0);
  if (!attachment)
    return false;
  return attachment->FormsFeedbackLoop(texture, level);
}
