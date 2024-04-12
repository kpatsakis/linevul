void WebGLRenderingContextBase::texSubImage2D(
    ExecutionContext* execution_context,
    GLenum target,
    GLint level,
    GLint xoffset,
    GLint yoffset,
    GLenum format,
    GLenum type,
    CanvasRenderingContextHost* context_host,
    ExceptionState& exception_state) {
  TexImageHelperCanvasRenderingContextHost(
      execution_context->GetSecurityOrigin(), kTexSubImage2D, target, level, 0,
      format, type, xoffset, yoffset, 0, context_host,
      GetTextureSourceSize(context_host), 1, 0, exception_state);
}
