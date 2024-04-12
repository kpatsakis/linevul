void WebGL2RenderingContextBase::copyBufferSubData(GLenum read_target,
                                                   GLenum write_target,
                                                   long long read_offset,
                                                   long long write_offset,
                                                   long long size) {
  if (isContextLost())
    return;

  if (!ValidateValueFitNonNegInt32("copyBufferSubData", "readOffset",
                                   read_offset) ||
      !ValidateValueFitNonNegInt32("copyBufferSubData", "writeOffset",
                                   write_offset) ||
      !ValidateValueFitNonNegInt32("copyBufferSubData", "size", size)) {
    return;
  }

  WebGLBuffer* read_buffer =
      ValidateBufferDataTarget("copyBufferSubData", read_target);
  if (!read_buffer)
    return;

  WebGLBuffer* write_buffer =
      ValidateBufferDataTarget("copyBufferSubData", write_target);
  if (!write_buffer)
    return;

  if (read_offset + size > read_buffer->GetSize() ||
      write_offset + size > write_buffer->GetSize()) {
    SynthesizeGLError(GL_INVALID_VALUE, "copyBufferSubData", "buffer overflow");
    return;
  }

  if ((write_buffer->GetInitialTarget() == GL_ELEMENT_ARRAY_BUFFER &&
       read_buffer->GetInitialTarget() != GL_ELEMENT_ARRAY_BUFFER) ||
      (write_buffer->GetInitialTarget() != GL_ELEMENT_ARRAY_BUFFER &&
       read_buffer->GetInitialTarget() == GL_ELEMENT_ARRAY_BUFFER)) {
    SynthesizeGLError(GL_INVALID_OPERATION, "copyBufferSubData",
                      "Cannot copy into an element buffer destination from a "
                      "non-element buffer source");
    return;
  }

  if (write_buffer->GetInitialTarget() == 0)
    write_buffer->SetInitialTarget(read_buffer->GetInitialTarget());

  ContextGL()->CopyBufferSubData(
      read_target, write_target, static_cast<GLintptr>(read_offset),
      static_cast<GLintptr>(write_offset), static_cast<GLsizeiptr>(size));
}
