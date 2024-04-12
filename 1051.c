GLenum GLES2DecoderImpl::GetBoundReadFrameBufferTextureType() {
  Framebuffer* framebuffer =
    GetFramebufferInfoForTarget(GL_READ_FRAMEBUFFER_EXT);
  if (framebuffer != NULL) {
    return framebuffer->GetColorAttachmentTextureType();
  } else {
    return GL_UNSIGNED_BYTE;
  }
}
