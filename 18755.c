error::Error GLES2DecoderPassthroughImpl::DoGetProgramInfoLog(
    GLuint program,
    std::string* infolog) {
  CheckErrorCallbackState();
  GLint info_log_len = 0;
  api()->glGetProgramivFn(GetProgramServiceID(program, resources_),
                          GL_INFO_LOG_LENGTH, &info_log_len);

  if (CheckErrorCallbackState()) {
    return error::kNoError;
  }

  std::vector<char> buffer(info_log_len, 0);
  GLsizei length = 0;
  api()->glGetProgramInfoLogFn(GetProgramServiceID(program, resources_),
                               info_log_len, &length, buffer.data());
  DCHECK(length <= info_log_len);
  *infolog = length > 0 ? std::string(buffer.data(), length) : std::string();
  return error::kNoError;
}
