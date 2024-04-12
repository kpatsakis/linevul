error::Error GLES2DecoderPassthroughImpl::DoBindFragDataLocationIndexedEXT(
    GLuint program,
    GLuint colorNumber,
    GLuint index,
    const char* name) {
  api()->glBindFragDataLocationIndexedFn(
      GetProgramServiceID(program, resources_), colorNumber, index, name);
  return error::kNoError;
}
