void WebGLRenderingContextBase::uniform2iv(const WebGLUniformLocation* location,
                                           const FlexibleInt32ArrayView& v) {
  if (isContextLost() || !ValidateUniformParameters<WTF::Int32Array>(
                             "uniform2iv", location, v, 2, 0, v.length()))
    return;

  ContextGL()->Uniform2iv(location->Location(), v.length() >> 1,
                          v.DataMaybeOnStack());
}
