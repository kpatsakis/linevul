GLuint GLES2DecoderImpl::DoGetMaxValueInBufferCHROMIUM(
    GLuint buffer_id, GLsizei count, GLenum type, GLuint offset) {
  GLuint max_vertex_accessed = 0;
  BufferManager::BufferInfo* info = GetBufferInfo(buffer_id);
  if (!info) {
    SetGLError(GL_INVALID_VALUE,
               "GetMaxValueInBufferCHROMIUM", "unknown buffer");
  } else {
    if (!info->GetMaxValueForRange(offset, count, type, &max_vertex_accessed)) {
      SetGLError(
          GL_INVALID_OPERATION,
          "GetMaxValueInBufferCHROMIUM", "range out of bounds for buffer");
    }
  }
  return max_vertex_accessed;
}
