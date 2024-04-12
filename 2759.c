void GLES2DecoderImpl::DoGetIntegerv(GLenum pname,
                                     GLint* params,
                                     GLsizei params_size) {
  DCHECK(params);
  GLsizei num_written = 0;
  if (state_.GetStateAsGLint(pname, params, &num_written) ||
      GetHelper(pname, params, &num_written)) {
    DCHECK_EQ(num_written, params_size);
    return;
  }
  NOTREACHED() << "Unhandled enum " << pname;
}
