error::Error GLES2DecoderPassthroughImpl::DoDeleteTextures(
    GLsizei n,
    const volatile GLuint* textures) {
  if (n < 0) {
    InsertError(GL_INVALID_VALUE, "n cannot be negative.");
    return error::kNoError;
  }

  std::vector<GLuint> non_mailbox_client_ids;
  for (GLsizei ii = 0; ii < n; ++ii) {
    GLuint client_id = textures[ii];
    scoped_refptr<TexturePassthrough> texture = nullptr;
    if (!resources_->texture_object_map.GetServiceID(client_id, &texture) ||
        texture == nullptr) {
      non_mailbox_client_ids.push_back(client_id);
    } else {
      resources_->texture_id_map.RemoveClientID(client_id);
      resources_->texture_object_map.RemoveClientID(client_id);
      resources_->texture_shared_image_map.erase(client_id);
      UpdateTextureBinding(texture->target(), client_id, nullptr);
    }

    group_->passthrough_discardable_manager()->DeleteTexture(client_id,
                                                             group_.get());
  }
  return DeleteHelper(
      non_mailbox_client_ids.size(), non_mailbox_client_ids.data(),
      &resources_->texture_id_map, [this](GLsizei n, GLuint* textures) {
        api()->glDeleteTexturesFn(n, textures);
      });
}
