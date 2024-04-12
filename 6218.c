error::Error GLES2DecoderPassthroughImpl::DoGetProgramInterfaceiv(
    GLuint program,
    GLenum program_interface,
    GLenum pname,
    GLsizei bufsize,
    GLsizei* length,
    GLint* params) {
  if (bufsize < 1) {
    return error::kOutOfBounds;
  }
  *length = 1;
  api()->glGetProgramInterfaceivFn(GetProgramServiceID(program, resources_),
                                   program_interface, pname, params);
  return error::kNoError;
}
