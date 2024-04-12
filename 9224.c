bool GLES2DecoderImpl::DoBindOrCopyTexImageIfNeeded(Texture* texture,
                                                    GLenum textarget,
                                                    GLuint texture_unit) {
  if (texture && !texture->IsAttachedToFramebuffer()) {
    Texture::ImageState image_state;
    gl::GLImage* image = texture->GetLevelImage(textarget, 0, &image_state);
    if (image && image_state == Texture::UNBOUND) {
      ScopedGLErrorSuppressor suppressor(
          "GLES2DecoderImpl::DoBindOrCopyTexImageIfNeeded", GetErrorState());
      if (texture_unit)
        api()->glActiveTextureFn(texture_unit);
      api()->glBindTextureFn(textarget, texture->service_id());
      if (image->BindTexImage(textarget)) {
        image_state = Texture::BOUND;
      } else {
        DoCopyTexImage(texture, textarget, image);
      }
      if (!texture_unit) {
        RestoreCurrentTextureBindings(&state_, textarget,
                                      state_.active_texture_unit);
        return false;
      }
      return true;
    }
  }
  return false;
}
