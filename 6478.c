void WebGL2RenderingContextBase::bufferData(
    GLenum target,
    MaybeShared<DOMArrayBufferView> src_data,
    GLenum usage,
    GLuint src_offset,
    GLuint length) {
  if (isContextLost())
    return;
  void* sub_base_address = nullptr;
  long long sub_byte_length = 0;
  if (!ValidateSubSourceAndGetData(src_data.View(), src_offset, length,
                                   &sub_base_address, &sub_byte_length)) {
    SynthesizeGLError(GL_INVALID_VALUE, "bufferData",
                      "srcOffset + length too large");
    return;
  }
  BufferDataImpl(target, sub_byte_length, sub_base_address, usage);
}
