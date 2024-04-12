void GLES2DecoderImpl::DoGetBufferParameteriv(GLenum target,
                                              GLenum pname,
                                              GLint* params,
                                              GLsizei params_size) {
  buffer_manager()->ValidateAndDoGetBufferParameteriv(
      &state_, error_state_.get(), target, pname, params);
}
