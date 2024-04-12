error::Error GLES2DecoderPassthroughImpl::DoUniform1i(GLint location, GLint x) {
  api()->glUniform1iFn(location, x);
  return error::kNoError;
}
