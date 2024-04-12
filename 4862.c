void GLES2DecoderPassthroughImpl::UpdateTextureBinding(
    GLenum target,
    GLuint client_id,
    TexturePassthrough* texture) {
  GLuint texture_service_id = texture ? texture->service_id() : 0;
  size_t cur_texture_unit = active_texture_unit_;
  auto& target_bound_textures =
      bound_textures_[static_cast<size_t>(GLenumToTextureTarget(target))];
  for (size_t bound_texture_index = 0;
       bound_texture_index < target_bound_textures.size();
       bound_texture_index++) {
    if (target_bound_textures[bound_texture_index].client_id == client_id) {
      if (bound_texture_index != cur_texture_unit) {
        api()->glActiveTextureFn(
            static_cast<GLenum>(GL_TEXTURE0 + bound_texture_index));
        cur_texture_unit = bound_texture_index;
      }

      api()->glBindTextureFn(target, texture_service_id);
      target_bound_textures[bound_texture_index].texture = texture;
    }
  }

  if (cur_texture_unit != active_texture_unit_) {
    api()->glActiveTextureFn(
        static_cast<GLenum>(GL_TEXTURE0 + active_texture_unit_));
  }
}
