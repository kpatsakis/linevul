void GLES2DecoderImpl::DoSamplerParameteriv(
    GLuint sampler, GLenum pname, const GLint* params) {
  DCHECK(params);
  glSamplerParameteri(sampler, pname, params[0]);
}
