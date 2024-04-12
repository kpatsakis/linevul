void WebGLRenderingContextBase::vertexAttrib1fv(
    GLuint index,
    MaybeShared<const DOMFloat32Array> v) {
  if (isContextLost())
    return;
  if (!v.View() || v.View()->length() < 1) {
    SynthesizeGLError(GL_INVALID_VALUE, "vertexAttrib1fv", "invalid array");
    return;
  }
  ContextGL()->VertexAttrib1fv(index, v.View()->DataMaybeShared());
  SetVertexAttribType(index, kFloat32ArrayType);
}
