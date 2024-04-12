void GLES2DecoderImpl::DoGenerateMipmap(GLenum target) {
  TextureRef* texture_ref = texture_manager()->GetTextureInfoForTarget(
      &state_, target);
  if (!texture_ref ||
      !texture_manager()->CanGenerateMipmaps(texture_ref)) {
    LOCAL_SET_GL_ERROR(
        GL_INVALID_OPERATION, "glGenerateMipmap", "Can not generate mips");
    return;
  }

  if (target == GL_TEXTURE_CUBE_MAP) {
    for (int i = 0; i < 6; ++i) {
      GLenum face = GL_TEXTURE_CUBE_MAP_POSITIVE_X + i;
      if (!texture_manager()->ClearTextureLevel(this, texture_ref, face, 0)) {
        LOCAL_SET_GL_ERROR(
            GL_OUT_OF_MEMORY, "glGenerateMipmap", "dimensions too big");
        return;
      }
    }
  } else {
    if (!texture_manager()->ClearTextureLevel(this, texture_ref, target, 0)) {
      LOCAL_SET_GL_ERROR(
          GL_OUT_OF_MEMORY, "glGenerateMipmap", "dimensions too big");
      return;
    }
  }

  LOCAL_COPY_REAL_GL_ERRORS_TO_WRAPPER("glGenerateMipmap");
  if (workarounds().set_texture_filter_before_generating_mipmap) {
    glTexParameteri(target, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_NEAREST);
  }
  glGenerateMipmapEXT(target);
  if (workarounds().set_texture_filter_before_generating_mipmap) {
    glTexParameteri(target, GL_TEXTURE_MIN_FILTER,
                    texture_ref->texture()->min_filter());
  }
  GLenum error = LOCAL_PEEK_GL_ERROR("glGenerateMipmap");
  if (error == GL_NO_ERROR) {
    texture_manager()->MarkMipmapsGenerated(texture_ref);
  }
}
