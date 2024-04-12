void WebGL2RenderingContextBase::uniformMatrix2fv(
    const WebGLUniformLocation* location,
    GLboolean transpose,
    Vector<GLfloat>& v) {
  WebGLRenderingContextBase::uniformMatrix2fv(location, transpose, v);
}
