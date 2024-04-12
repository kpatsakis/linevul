void WebGLRenderingContextBase::BufferSubDataImpl(GLenum target,
                                                  long long offset,
                                                  GLsizeiptr size,
                                                  const void* data) {
  WebGLBuffer* buffer = ValidateBufferDataTarget("bufferSubData", target);
  if (!buffer)
    return;
  if (!ValidateValueFitNonNegInt32("bufferSubData", "offset", offset))
    return;
  if (!data)
    return;
  if (offset + static_cast<long long>(size) > buffer->GetSize()) {
    SynthesizeGLError(GL_INVALID_VALUE, "bufferSubData", "buffer overflow");
    return;
  }

  ContextGL()->BufferSubData(target, static_cast<GLintptr>(offset), size, data);
}
