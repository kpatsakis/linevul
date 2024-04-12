GLsync GLES2DecoderImpl::DoFenceSync(GLenum condition, GLbitfield flags) {
  const char* function_name = "glFenceSync";
  if (condition != GL_SYNC_GPU_COMMANDS_COMPLETE) {
    LOCAL_SET_GL_ERROR(GL_INVALID_ENUM, function_name, "invalid condition");
    return 0;
  }
  if (flags != 0) {
    LOCAL_SET_GL_ERROR(GL_INVALID_VALUE, function_name, "invalid flags");
    return 0;
  }
  return api()->glFenceSyncFn(condition, flags);
}
