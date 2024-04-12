error::Error GLES2DecoderPassthroughImpl::DoUniform4fv(
    GLint location,
    GLsizei count,
    const volatile GLfloat* v) {
  api()->glUniform4fvFn(location, count, const_cast<const GLfloat*>(v));
  return error::kNoError;
}
