error::Error GLES2DecoderPassthroughImpl::DoGetActiveUniformBlockiv(
    GLuint program,
    GLuint index,
    GLenum pname,
    GLsizei bufSize,
    GLsizei* length,
    GLint* params) {
  api()->glGetActiveUniformBlockivRobustANGLEFn(
      GetProgramServiceID(program, resources_), index, pname, bufSize, length,
      params);
  return error::kNoError;
}
