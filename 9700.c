void WebGL2RenderingContextBase::uniformMatrix2x4fv(
    const WebGLUniformLocation* location,
    GLboolean transpose,
    MaybeShared<DOMFloat32Array> value,
    GLuint src_offset,
    GLuint src_length) {
  if (isContextLost() || !ValidateUniformMatrixParameters(
                             "uniformMatrix2x4fv", location, transpose,
                             value.View(), 8, src_offset, src_length))
    return;
  ContextGL()->UniformMatrix2x4fv(
      location->Location(),
      (src_length ? src_length : (value.View()->length() - src_offset)) >> 3,
      transpose, value.View()->DataMaybeShared() + src_offset);
}
