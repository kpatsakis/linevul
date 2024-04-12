error::Error GLES2DecoderPassthroughImpl::DoGenRenderbuffers(
    GLsizei n,
    volatile GLuint* renderbuffers) {
  return GenHelper(n, renderbuffers, &resources_->renderbuffer_id_map,
                   [this](GLsizei n, GLuint* renderbuffers) {
                     api()->glGenRenderbuffersEXTFn(n, renderbuffers);
                   });
}
