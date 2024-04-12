error::Error GLES2DecoderPassthroughImpl::DoGetUniformLocation(
    GLuint program,
    const char* name,
    GLint* location) {
  *location = api()->glGetUniformLocationFn(
      GetProgramServiceID(program, resources_), name);
  return error::kNoError;
}
