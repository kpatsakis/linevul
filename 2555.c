void* GLES2Implementation::MapBufferCHROMIUM(GLuint target, GLenum access) {
  GPU_CLIENT_SINGLE_THREAD_CHECK();
  GPU_CLIENT_LOG("[" << GetLogPrefix() << "] glMapBufferCHROMIUM(" << target
                     << ", " << GLES2Util::GetStringEnum(access) << ")");
  switch (target) {
    case GL_PIXEL_PACK_TRANSFER_BUFFER_CHROMIUM:
      if (access != GL_READ_ONLY) {
        SetGLError(GL_INVALID_ENUM, "glMapBufferCHROMIUM", "bad access mode");
        return nullptr;
      }
      break;
    default:
      SetGLError(GL_INVALID_ENUM, "glMapBufferCHROMIUM", "invalid target");
      return nullptr;
  }
  GLuint buffer_id;
  GetBoundPixelTransferBuffer(target, "glMapBufferCHROMIUM", &buffer_id);
  if (!buffer_id) {
    return nullptr;
  }
  BufferTracker::Buffer* buffer = buffer_tracker_->GetBuffer(buffer_id);
  if (!buffer) {
    SetGLError(GL_INVALID_OPERATION, "glMapBufferCHROMIUM", "invalid buffer");
    return nullptr;
  }
  if (buffer->mapped()) {
    SetGLError(GL_INVALID_OPERATION, "glMapBufferCHROMIUM", "already mapped");
    return nullptr;
  }
  if (buffer->last_usage_token()) {
    helper_->WaitForToken(buffer->last_usage_token());
    buffer->set_last_usage_token(0);
  }
  buffer->set_mapped(true);

  GPU_CLIENT_LOG("  returned " << buffer->address());
  CheckGLError();
  return buffer->address();
}
