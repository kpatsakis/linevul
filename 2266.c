void GLES2DecoderImpl::DoGetIntegeri_v(GLenum target,
                                       GLuint index,
                                       GLint* params,
                                       GLsizei params_size) {
  GetIndexedIntegerImpl<GLint>("glGetIntegeri_v", target, index, params);
}
