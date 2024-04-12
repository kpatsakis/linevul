void GLES2DecoderImpl::ClearFramebufferForWorkaround(GLbitfield mask) {
  ScopedGLErrorSuppressor suppressor("GLES2DecoderImpl::ClearWorkaround",
                                     error_state_.get());
  clear_framebuffer_blit_->ClearFramebuffer(
      this, gfx::Size(viewport_max_width_, viewport_max_height_), mask,
      state_.color_clear_red, state_.color_clear_green, state_.color_clear_blue,
      state_.color_clear_alpha, state_.depth_clear, state_.stencil_clear);
}
