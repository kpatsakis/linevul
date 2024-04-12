GLboolean GLES2Implementation::UnmapBuffer(GLenum target) {
  GPU_CLIENT_SINGLE_THREAD_CHECK();
  GPU_CLIENT_LOG("[" << GetLogPrefix() << "] glUnmapBuffer("
                     << GLES2Util::GetStringEnum(target) << ")");
  switch (target) {
    case GL_ARRAY_BUFFER:
    case GL_ATOMIC_COUNTER_BUFFER:
    case GL_ELEMENT_ARRAY_BUFFER:
    case GL_COPY_READ_BUFFER:
    case GL_COPY_WRITE_BUFFER:
    case GL_PIXEL_PACK_BUFFER:
    case GL_PIXEL_UNPACK_BUFFER:
    case GL_SHADER_STORAGE_BUFFER:
    case GL_TRANSFORM_FEEDBACK_BUFFER:
    case GL_UNIFORM_BUFFER:
      break;
    default:
      SetGLError(GL_INVALID_ENUM, "glUnmapBuffer", "invalid target");
      return GL_FALSE;
  }
  GLuint buffer = GetBoundBufferHelper(target);
  if (buffer == 0) {
    SetGLError(GL_INVALID_OPERATION, "glUnmapBuffer", "no buffer bound");
    return GL_FALSE;
  }
  auto iter = mapped_buffer_range_map_.find(buffer);
  if (iter == mapped_buffer_range_map_.end()) {
    SetGLError(GL_INVALID_OPERATION, "glUnmapBuffer", "buffer is unmapped");
    return GL_FALSE;
  }

  bool was_mapped_by_readback_tracker = false;
  if (auto* buffer_object =
          readback_buffer_shadow_tracker_->GetBuffer(buffer)) {
    was_mapped_by_readback_tracker = buffer_object->UnmapReadbackShm();
  }
  if (!was_mapped_by_readback_tracker) {
    helper_->UnmapBuffer(target);
    InvalidateReadbackBufferShadowDataCHROMIUM(GetBoundBufferHelper(target));
  }
  RemoveMappedBufferRangeById(buffer);

  GPU_CLIENT_LOG("  returned " << GL_TRUE);
  CheckGLError();
  return GL_TRUE;
}
