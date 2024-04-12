error::Error GLES2DecoderPassthroughImpl::DoGetAttribLocation(GLuint program,
                                                              const char* name,
                                                              GLint* result) {
  *result = api()->glGetAttribLocationFn(
      GetProgramServiceID(program, resources_), name);
  return error::kNoError;
}
