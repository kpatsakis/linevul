bool WebGLRenderingContextBase::ValidateStencilSettings(
    const char* function_name) {
  if (stencil_mask_ != stencil_mask_back_ ||
      stencil_func_ref_ != stencil_func_ref_back_ ||
      stencil_func_mask_ != stencil_func_mask_back_) {
    SynthesizeGLError(GL_INVALID_OPERATION, function_name,
                      "front and back stencils settings do not match");
    return false;
  }
  return true;
}
