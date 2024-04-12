bool GLES2DecoderImpl::ValidateCompressedTexSubDimensions(
    const char* function_name,
    GLenum target, GLint level, GLint xoffset, GLint yoffset,
    GLsizei width, GLsizei height, GLenum format,
    TextureManager::TextureInfo* texture) {
  if (xoffset < 0 || yoffset < 0) {
    SetGLError(
        GL_INVALID_VALUE, function_name, "xoffset or yoffset < 0");
    return false;
  }

  switch (format) {
    case GL_COMPRESSED_RGB_S3TC_DXT1_EXT:
    case GL_COMPRESSED_RGBA_S3TC_DXT1_EXT:
    case GL_COMPRESSED_RGBA_S3TC_DXT3_EXT:
    case GL_COMPRESSED_RGBA_S3TC_DXT5_EXT: {
      const int kBlockWidth = 4;
      const int kBlockHeight = 4;
      if ((xoffset % kBlockWidth) || (yoffset % kBlockHeight)) {
        SetGLError(
            GL_INVALID_OPERATION, function_name,
            "xoffset or yoffset not multiple of 4");
        return false;
      }
      GLsizei tex_width = 0;
      GLsizei tex_height = 0;
      if (!texture->GetLevelSize(target, level, &tex_width, &tex_height) ||
          width - xoffset > tex_width ||
          height - yoffset > tex_height) {
        SetGLError(
            GL_INVALID_OPERATION, function_name, "dimensions out of range");
        return false;
      }
      return ValidateCompressedTexDimensions(
          function_name, level, width, height, format);
    }
    default:
      return false;
  }
}
