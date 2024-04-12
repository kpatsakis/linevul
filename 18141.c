error::Error GLES2DecoderPassthroughImpl::DoDeleteRenderbuffers(
    GLsizei n,
    const volatile GLuint* renderbuffers) {
  if (n < 0) {
    InsertError(GL_INVALID_VALUE, "n cannot be negative.");
    return error::kNoError;
  }
  return DeleteHelper(n, renderbuffers, &resources_->renderbuffer_id_map,
                      [this](GLsizei n, GLuint* renderbuffers) {
                        api()->glDeleteRenderbuffersEXTFn(n, renderbuffers);
                      });
}
