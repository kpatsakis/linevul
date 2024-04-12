GLint GLES2Implementation::GetProgramResourceLocation(
    GLuint program,
    GLenum program_interface,
    const char* name) {
  GPU_CLIENT_SINGLE_THREAD_CHECK();
  GPU_CLIENT_LOG("[" << GetLogPrefix() << "] glGetProgramResourceLocation("
                     << program << ", " << program_interface << ", " << name
                     << ")");
  TRACE_EVENT0("gpu", "GLES2::GetProgramResourceLocation");
  GLint location =
      share_group_->program_info_manager()->GetProgramResourceLocation(
          this, program, program_interface, name);
  GPU_CLIENT_LOG("returned " << location);
  CheckGLError();
  return location;
}
