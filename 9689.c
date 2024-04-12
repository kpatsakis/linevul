void GLES2Implementation::GetUniformBlocksCHROMIUM(GLuint program,
                                                   GLsizei bufsize,
                                                   GLsizei* size,
                                                   void* info) {
  GPU_CLIENT_SINGLE_THREAD_CHECK();
  if (bufsize < 0) {
    SetGLError(GL_INVALID_VALUE, "glGetUniformBlocksCHROMIUM",
               "bufsize less than 0.");
    return;
  }
  if (size == nullptr) {
    SetGLError(GL_INVALID_VALUE, "glGetUniformBlocksCHROMIUM", "size is null.");
    return;
  }
  DCHECK_EQ(0, *size);
  std::vector<int8_t> result;
  GetUniformBlocksCHROMIUMHelper(program, &result);
  if (result.empty()) {
    return;
  }
  *size = result.size();
  if (!info) {
    return;
  }
  if (static_cast<size_t>(bufsize) < result.size()) {
    SetGLError(GL_INVALID_OPERATION, "glGetUniformBlocksCHROMIUM",
               "bufsize is too small for result.");
    return;
  }
  memcpy(info, &result[0], result.size());
}
