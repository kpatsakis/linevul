error::Error GLES2DecoderPassthroughImpl::DoUniform2iv(
    GLint location,
    GLsizei count,
    const volatile GLint* v) {
  api()->glUniform2ivFn(location, count, const_cast<const GLint*>(v));
  return error::kNoError;
}
