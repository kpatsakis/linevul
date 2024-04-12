bool GLES2DecoderImpl::IsDrawValid(
    const char* function_name, GLuint max_vertex_accessed, bool instanced,
    GLsizei primcount) {
  DCHECK(instanced || primcount == 1);

  if (!state_.current_program.get()) {
    LOCAL_RENDER_WARNING("Drawing with no current shader program.");
    return false;
  }

  if (!feature_info_->feature_flags().separate_stencil_ref_mask_writemask) {
    if (!ValidateStencilStateForDraw(function_name)) {
      return false;
    }
  }

  if (CheckDrawingFeedbackLoops()) {
    LOCAL_SET_GL_ERROR(
        GL_INVALID_OPERATION, function_name,
        "Source and destination textures of the draw are the same.");
    return false;
  }

  if (!state_.vertex_attrib_manager->ValidateBindings(
          function_name, this, feature_info_.get(), buffer_manager(),
          state_.current_program.get(), max_vertex_accessed, instanced,
          primcount)) {
    return false;
  }

  if (workarounds().disallow_large_instanced_draw) {
    const GLsizei kMaxInstancedDrawPrimitiveCount = 0x4000000;
    if (primcount > kMaxInstancedDrawPrimitiveCount) {
      LOCAL_SET_GL_ERROR(
          GL_OUT_OF_MEMORY, function_name,
          "Instanced draw primcount too large for this platform");
      return false;
    }
  }

  return true;
}
