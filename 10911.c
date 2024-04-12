bool GLES2DecoderImpl::SetCapabilityState(GLenum cap, bool enabled) {
  switch (cap) {
    case GL_SCISSOR_TEST:
      enable_scissor_test_ = enabled;
      return true;
    case GL_DEPTH_TEST: {
      if (enable_depth_test_ != enabled) {
        enable_depth_test_ = enabled;
        state_dirty_ = true;
      }
      return false;
    }
    case GL_STENCIL_TEST:
      if (enable_stencil_test_ != enabled) {
        enable_stencil_test_ = enabled;
        state_dirty_ = true;
      }
      return false;
    default:
      return true;
  }
}
