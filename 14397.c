void WebGLRenderingContextBase::texSubImage2D(
    ExecutionContext* execution_context,
    GLenum target,
    GLint level,
    GLint xoffset,
    GLint yoffset,
    GLenum format,
    GLenum type,
    HTMLCanvasElement* canvas,
    ExceptionState& exception_state) {
  TexImageHelperHTMLCanvasElement(
      execution_context->GetSecurityOrigin(), kTexSubImage2D, target, level, 0,
      format, type, xoffset, yoffset, 0, canvas, GetTextureSourceSize(canvas),
      1, 0, exception_state);
}
