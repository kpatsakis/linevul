bool WebGL2RenderingContextBase::ValidateGetFramebufferAttachmentParameterFunc(
    const char* function_name,
    GLenum target,
    GLenum attachment) {
  if (!ValidateFramebufferTarget(target)) {
    SynthesizeGLError(GL_INVALID_ENUM, function_name, "invalid target");
    return false;
  }

  WebGLFramebuffer* framebuffer_binding = GetFramebufferBinding(target);
  DCHECK(framebuffer_binding || GetDrawingBuffer());
  if (!framebuffer_binding) {
    switch (attachment) {
      case GL_BACK:
      case GL_DEPTH:
      case GL_STENCIL:
        break;
      default:
        SynthesizeGLError(GL_INVALID_ENUM, function_name, "invalid attachment");
        return false;
    }
  } else {
    switch (attachment) {
      case GL_COLOR_ATTACHMENT0:
      case GL_DEPTH_ATTACHMENT:
      case GL_STENCIL_ATTACHMENT:
        break;
      case GL_DEPTH_STENCIL_ATTACHMENT:
        if (framebuffer_binding->GetAttachmentObject(GL_DEPTH_ATTACHMENT) !=
            framebuffer_binding->GetAttachmentObject(GL_STENCIL_ATTACHMENT)) {
          SynthesizeGLError(GL_INVALID_OPERATION, function_name,
                            "different objects are bound to the depth and "
                            "stencil attachment points");
          return false;
        }
        break;
      default:
        if (attachment > GL_COLOR_ATTACHMENT0 &&
            attachment < static_cast<GLenum>(GL_COLOR_ATTACHMENT0 +
                                             MaxColorAttachments()))
          break;
        SynthesizeGLError(GL_INVALID_ENUM, function_name, "invalid attachment");
        return false;
    }
  }
  return true;
}
