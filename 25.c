void WebGLRenderingContextBase::uniformMatrix4fv(
    const WebGLUniformLocation* location,
    GLboolean transpose,
    MaybeShared<DOMFloat32Array> v) {
  if (isContextLost() ||
      !ValidateUniformMatrixParameters("uniformMatrix4fv", location, transpose,
                                       v.View(), 16, 0, v.View()->length()))
    return;
  ContextGL()->UniformMatrix4fv(location->Location(), v.View()->length() >> 4,
                                transpose, v.View()->DataMaybeShared());
}
