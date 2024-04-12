void GLES2DecoderImpl::DoBufferData(
    GLenum target, GLsizeiptr size, const GLvoid * data, GLenum usage) {
  if (!validators_->buffer_target.IsValid(target)) {
    SetGLErrorInvalidEnum("glBufferData", target, "target");
    return;
  }
  if (!validators_->buffer_usage.IsValid(usage)) {
    SetGLErrorInvalidEnum("glBufferData", usage, "usage");
    return;
  }
  if (size < 0) {
    SetGLError(GL_INVALID_VALUE, "glBufferData", "size < 0");
    return;
  }
  BufferManager::BufferInfo* info = GetBufferInfoForTarget(target);
  if (!info) {
    SetGLError(GL_INVALID_VALUE, "glBufferData", "unknown buffer");
    return;
  }
  scoped_array<int8> zero;
  if (!data) {
    zero.reset(new int8[size]);
    memset(zero.get(), 0, size);
    data = zero.get();
  }

  if (!bufferdata_faster_than_buffersubdata_ &&
      size == info->size() && usage == info->usage()) {
    glBufferSubData(target, 0, size, data);
    info->SetRange(0, size, data);
    return;
  }

  CopyRealGLErrorsToWrapper();
  glBufferData(target, size, data, usage);
  GLenum error = PeekGLError();
  if (error == GL_NO_ERROR) {
    buffer_manager()->SetInfo(info, size, usage);
    info->SetRange(0, size, data);
  }
}
