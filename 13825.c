bool WebGLRenderingContextBase::ValidateFramebufferTarget(GLenum target) {
  if (target == GL_FRAMEBUFFER)
    return true;
  return false;
}
