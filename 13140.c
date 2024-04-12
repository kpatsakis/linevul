void WebGL2RenderingContextBase::uniform3uiv(
    const WebGLUniformLocation* location,
    const FlexibleUint32ArrayView& v,
    GLuint src_offset,
    GLuint src_length) {
  if (isContextLost() ||
      !ValidateUniformParameters<WTF::Uint32Array>("uniform3uiv", location, v,
                                                   3, src_offset, src_length))
    return;

  ContextGL()->Uniform3uiv(
      location->Location(),
      (src_length ? src_length : (v.length() - src_offset)) / 3,
      v.DataMaybeOnStack() + src_offset);
}
