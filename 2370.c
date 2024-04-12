error::Error GLES2DecoderPassthroughImpl::DoDeleteSamplers(
    GLsizei n,
    const volatile GLuint* samplers) {
  if (n < 0) {
    InsertError(GL_INVALID_VALUE, "n cannot be negative.");
    return error::kNoError;
  }
  return DeleteHelper(n, samplers, &resources_->sampler_id_map,
                      [this](GLsizei n, GLuint* samplers) {
                        api()->glDeleteSamplersFn(n, samplers);
                      });
}
