void GLES2DecoderImpl::BindTexImage2DCHROMIUMImpl(const char* function_name,
                                                  GLenum target,
                                                  GLenum internalformat,
                                                  GLint image_id) {
  if (target == GL_TEXTURE_CUBE_MAP) {
    LOCAL_SET_GL_ERROR(GL_INVALID_ENUM, function_name, "invalid target");
    return;
  }

  TextureRef* texture_ref =
      texture_manager()->GetTextureInfoForTargetUnlessDefault(&state_, target);
  if (!texture_ref) {
    LOCAL_SET_GL_ERROR(GL_INVALID_OPERATION, function_name, "no texture bound");
    return;
  }

  gl::GLImage* image = image_manager()->LookupImage(image_id);
  if (!image) {
    LOCAL_SET_GL_ERROR(GL_INVALID_OPERATION, function_name,
                       "no image found with the given ID");
    return;
  }

  Texture::ImageState image_state = Texture::UNBOUND;

  if (image->ShouldBindOrCopy() == gl::GLImage::BIND) {
    ScopedGLErrorSuppressor suppressor(
        "GLES2DecoderImpl::DoBindTexImage2DCHROMIUM", error_state_.get());

    if (internalformat) {
      if (image->BindTexImageWithInternalformat(target, internalformat))
        image_state = Texture::BOUND;
    } else {
      if (image->BindTexImage(target))
        image_state = Texture::BOUND;
    }
  }

  gfx::Size size = image->GetSize();
  GLenum texture_internalformat =
      internalformat ? internalformat : image->GetInternalFormat();
  texture_manager()->SetLevelInfo(
      texture_ref, target, 0, texture_internalformat, size.width(),
      size.height(), 1, 0,
      TextureManager::ExtractFormatFromStorageFormat(texture_internalformat),
      GL_UNSIGNED_BYTE, gfx::Rect(size));
  texture_manager()->SetLevelImage(texture_ref, target, 0, image, image_state);
}
