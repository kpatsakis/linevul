bool WebGLRenderingContextBase::ValidateReadBufferAndGetInfo(
    const char* function_name,
    WebGLFramebuffer*& read_framebuffer_binding) {
  read_framebuffer_binding = GetReadFramebufferBinding();
  if (read_framebuffer_binding) {
    const char* reason = "framebuffer incomplete";
    if (read_framebuffer_binding->CheckDepthStencilStatus(&reason) !=
        GL_FRAMEBUFFER_COMPLETE) {
      SynthesizeGLError(GL_INVALID_FRAMEBUFFER_OPERATION, function_name,
                        reason);
      return false;
    }
  } else {
    if (read_buffer_of_default_framebuffer_ == GL_NONE) {
      DCHECK(IsWebGL2OrHigher());
      SynthesizeGLError(GL_INVALID_OPERATION, function_name,
                        "no image to read from");
      return false;
    }
  }
  return true;
}
