error::Error GLES2DecoderPassthroughImpl::DoUniform2uiv(
    GLint location,
    GLsizei count,
    const volatile GLuint* v) {
  api()->glUniform2uivFn(location, count, const_cast<const GLuint*>(v));
  return error::kNoError;
}
