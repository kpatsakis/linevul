bool GLES2DecoderImpl::ValidateStencilStateForDraw(const char* function_name) {
  if (!state_.stencil_state_changed_since_validation) {
    return true;
  }

  GLenum stencil_format = GetBoundFramebufferStencilFormat(GL_DRAW_FRAMEBUFFER);
  uint8_t stencil_bits = GLES2Util::StencilBitsPerPixel(stencil_format);

  if (state_.enable_flags.stencil_test && stencil_bits > 0) {
    DCHECK_LE(stencil_bits, 8U);

    GLuint max_stencil_value = (1 << stencil_bits) - 1;
    GLint max_stencil_ref = static_cast<GLint>(max_stencil_value);
    bool different_refs =
        base::ClampToRange(state_.stencil_front_ref, 0, max_stencil_ref) !=
        base::ClampToRange(state_.stencil_back_ref, 0, max_stencil_ref);
    bool different_writemasks =
        (state_.stencil_front_writemask & max_stencil_value) !=
        (state_.stencil_back_writemask & max_stencil_value);
    bool different_value_masks =
        (state_.stencil_front_mask & max_stencil_value) !=
        (state_.stencil_back_mask & max_stencil_value);
    if (different_refs || different_writemasks || different_value_masks) {
      LOCAL_SET_GL_ERROR(GL_INVALID_OPERATION, function_name,
                         "Front/back stencil settings do not match.");
      return false;
    }
  }

  state_.stencil_state_changed_since_validation = false;
  return true;
}
