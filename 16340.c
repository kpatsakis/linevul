error::Error GLES2DecoderPassthroughImpl::DoGetSamplerParameterfv(
    GLuint sampler,
    GLenum pname,
    GLsizei bufsize,
    GLsizei* length,
    GLfloat* params) {
  api()->glGetSamplerParameterfvRobustANGLEFn(
      GetSamplerServiceID(sampler, resources_), pname, bufsize, length, params);
  return error::kNoError;
}
