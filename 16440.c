error::Error GLES2DecoderImpl::DoCompressedTexImage2D(
  GLenum target,
  GLint level,
  GLenum internal_format,
  GLsizei width,
  GLsizei height,
  GLint border,
  GLsizei image_size,
  const void* data) {
  if (!validators_->texture_target.IsValid(target)) {
    LOCAL_SET_GL_ERROR_INVALID_ENUM(
        "glCompressedTexImage2D", target, "target");
    return error::kNoError;
  }
  if (!validators_->compressed_texture_format.IsValid(
      internal_format)) {
    LOCAL_SET_GL_ERROR_INVALID_ENUM(
        "glCompressedTexImage2D", internal_format, "internal_format");
    return error::kNoError;
  }
  if (!texture_manager()->ValidForTarget(target, level, width, height, 1) ||
      border != 0) {
    LOCAL_SET_GL_ERROR(
        GL_INVALID_VALUE,
        "glCompressedTexImage2D", "dimensions out of range");
    return error::kNoError;
  }
  TextureRef* texture_ref = texture_manager()->GetTextureInfoForTarget(
      &state_, target);
  if (!texture_ref) {
    LOCAL_SET_GL_ERROR(
        GL_INVALID_VALUE,
        "glCompressedTexImage2D", "unknown texture target");
    return error::kNoError;
  }
  Texture* texture = texture_ref->texture();
  if (texture->IsImmutable()) {
    LOCAL_SET_GL_ERROR(
        GL_INVALID_OPERATION,
        "glCompressedTexImage2D", "texture is immutable");
    return error::kNoError;
  }

  if (!ValidateCompressedTexDimensions(
      "glCompressedTexImage2D", level, width, height, internal_format) ||
      !ValidateCompressedTexFuncData(
      "glCompressedTexImage2D", width, height, internal_format, image_size)) {
    return error::kNoError;
  }

  if (!EnsureGPUMemoryAvailable(image_size)) {
    LOCAL_SET_GL_ERROR(
        GL_OUT_OF_MEMORY, "glCompressedTexImage2D", "out of memory");
    return error::kNoError;
  }

  if (texture->IsAttachedToFramebuffer()) {
    framebuffer_state_.clear_state_dirty = true;
  }

  scoped_ptr<int8[]> zero;
  if (!data) {
    zero.reset(new int8[image_size]);
    memset(zero.get(), 0, image_size);
    data = zero.get();
  }
  LOCAL_COPY_REAL_GL_ERRORS_TO_WRAPPER("glCompressedTexImage2D");
  glCompressedTexImage2D(
      target, level, internal_format, width, height, border, image_size, data);
  GLenum error = LOCAL_PEEK_GL_ERROR("glCompressedTexImage2D");
  if (error == GL_NO_ERROR) {
    texture_manager()->SetLevelInfo(
        texture_ref, target, level, internal_format,
        width, height, 1, border, 0, 0, true);
  }
  return error::kNoError;
}
