void GLES2DecoderImpl::UnbindTexture(TextureRef* texture_ref,
                                     bool supports_separate_framebuffer_binds) {
  Texture* texture = texture_ref->texture();
  if (texture->IsAttachedToFramebuffer()) {
    framebuffer_state_.clear_state_dirty = true;
  }
  state_.UnbindTexture(texture_ref);

  if (supports_separate_framebuffer_binds) {
    if (framebuffer_state_.bound_read_framebuffer.get()) {
      framebuffer_state_.bound_read_framebuffer->UnbindTexture(
          GL_READ_FRAMEBUFFER_EXT, texture_ref);
    }
    if (framebuffer_state_.bound_draw_framebuffer.get()) {
      framebuffer_state_.bound_draw_framebuffer->UnbindTexture(
          GL_DRAW_FRAMEBUFFER_EXT, texture_ref);
    }
  } else {
    if (framebuffer_state_.bound_draw_framebuffer.get()) {
      framebuffer_state_.bound_draw_framebuffer->UnbindTexture(GL_FRAMEBUFFER,
                                                               texture_ref);
    }
  }
}
