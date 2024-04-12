error::Error GLES2DecoderPassthroughImpl::DoGetProgramResourceIndex(
    GLuint program,
    GLenum program_interface,
    const char* name,
    GLuint* index) {
  *index = api()->glGetProgramResourceIndexFn(
      GetProgramServiceID(program, resources_), program_interface, name);
  return error::kNoError;
}
