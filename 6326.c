void WebGLRenderingContextBase::framebufferRenderbuffer(
    GLenum target,
    GLenum attachment,
    GLenum renderbuffertarget,
    WebGLRenderbuffer* buffer) {
  if (isContextLost() || !ValidateFramebufferFuncParameters(
                             "framebufferRenderbuffer", target, attachment))
    return;
  if (renderbuffertarget != GL_RENDERBUFFER) {
    SynthesizeGLError(GL_INVALID_ENUM, "framebufferRenderbuffer",
                      "invalid target");
    return;
  }
  if (buffer && (!buffer->HasEverBeenBound() ||
                 !buffer->Validate(ContextGroup(), this))) {
    SynthesizeGLError(GL_INVALID_OPERATION, "framebufferRenderbuffer",
                      "buffer never bound or buffer not from this context");
    return;
  }
  WebGLFramebuffer* framebuffer_binding = GetFramebufferBinding(target);
  if (!framebuffer_binding || !framebuffer_binding->Object()) {
    SynthesizeGLError(GL_INVALID_OPERATION, "framebufferRenderbuffer",
                      "no framebuffer bound");
    return;
  }
  framebuffer_binding->SetAttachmentForBoundFramebuffer(target, attachment,
                                                        buffer);
  ApplyStencilTest();
}
