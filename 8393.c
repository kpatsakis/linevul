void GLES2Implementation::GetProgramResourceiv(GLuint program,
                                               GLenum program_interface,
                                               GLuint index,
                                               GLsizei prop_count,
                                               const GLenum* props,
                                               GLsizei bufsize,
                                               GLsizei* length,
                                               GLint* params) {
  GPU_CLIENT_SINGLE_THREAD_CHECK();
  GPU_CLIENT_LOG("[" << GetLogPrefix() << "] glGetProgramResourceiv(" << program
                     << ", " << program_interface << ", " << index << ", "
                     << prop_count << ", " << static_cast<const void*>(props)
                     << ", " << bufsize << ", " << static_cast<void*>(length)
                     << ", " << static_cast<void*>(params) << ")");
  if (prop_count < 0) {
    SetGLError(GL_INVALID_VALUE, "glGetProgramResourceiv", "prop_count < 0");
    return;
  }
  if (bufsize < 0) {
    SetGLError(GL_INVALID_VALUE, "glGetProgramResourceiv", "bufsize < 0");
    return;
  }
  TRACE_EVENT0("gpu", "GLES2::GetProgramResourceiv");
  GLsizei param_count = 0;
  bool success = share_group_->program_info_manager()->GetProgramResourceiv(
      this, program, program_interface, index, prop_count, props, bufsize,
      &param_count, params);
  if (length) {
    *length = param_count;
  }
  if (success && params) {
    GPU_CLIENT_LOG_CODE_BLOCK({
      for (GLsizei ii = 0; ii < param_count; ++ii) {
        GPU_CLIENT_LOG("  " << ii << ": " << params[ii]);
      }
    });
  }
  CheckGLError();
}
