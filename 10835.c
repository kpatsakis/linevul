error::Error GLES2DecoderPassthroughImpl::DoGetUniformiv(GLuint program,
                                                         GLint location,
                                                         GLsizei bufsize,
                                                         GLsizei* length,
                                                         GLint* params) {
  api()->glGetUniformivRobustANGLEFn(GetProgramServiceID(program, resources_),
                                     location, bufsize * sizeof(*params),
                                     length, params);
  return error::kNoError;
}
