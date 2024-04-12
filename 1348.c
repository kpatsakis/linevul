error::Error GLES2DecoderPassthroughImpl::DoReleaseTexImage2DCHROMIUM(
    GLenum target,
    GLint imageId) {
  if (target != GL_TEXTURE_2D) {
    InsertError(GL_INVALID_ENUM, "Invalid target");
    return error::kNoError;
  }

  const BoundTexture& bound_texture =
      bound_textures_[static_cast<size_t>(TextureTarget::k2D)]
                     [active_texture_unit_];
  if (bound_texture.texture == nullptr) {
    InsertError(GL_INVALID_OPERATION, "No texture bound");
    return error::kNoError;
  }

  gl::GLImage* image = group_->image_manager()->LookupImage(imageId);
  if (image == nullptr) {
    InsertError(GL_INVALID_OPERATION, "No image found with the given ID");
    return error::kNoError;
  }

  if (bound_texture.texture->GetLevelImage(target, 0) == image) {
    image->ReleaseTexImage(target);
    bound_texture.texture->SetLevelImage(target, 0, nullptr);
  }

  UpdateTextureSizeFromTarget(target);

  return error::kNoError;
}
