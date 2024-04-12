error::Error GLES2DecoderPassthroughImpl::DoGenTextures(
    GLsizei n,
    volatile GLuint* textures) {
  return GenHelper(n, textures, &resources_->texture_id_map,
                   [this](GLsizei n, GLuint* textures) {
                     api()->glGenTexturesFn(n, textures);
                   });
}
