static GLenum ExtractTypeFromStorageFormat(GLenum internalformat) {
  switch (internalformat) {
    case GL_RGB565:
      return GL_UNSIGNED_SHORT_5_6_5;
    case GL_RGBA4:
      return GL_UNSIGNED_SHORT_4_4_4_4;
    case GL_RGB5_A1:
      return GL_UNSIGNED_SHORT_5_5_5_1;
    case GL_RGB8_OES:
      return GL_UNSIGNED_BYTE;
    case GL_RGBA8_OES:
      return GL_UNSIGNED_BYTE;
    case GL_LUMINANCE8_ALPHA8_EXT:
      return GL_UNSIGNED_BYTE;
    case GL_LUMINANCE8_EXT:
      return GL_UNSIGNED_BYTE;
    case GL_ALPHA8_EXT:
      return GL_UNSIGNED_BYTE;
    case GL_RGBA32F_EXT:
      return GL_FLOAT;
    case GL_RGB32F_EXT:
      return GL_FLOAT;
    case GL_ALPHA32F_EXT:
      return GL_FLOAT;
    case GL_LUMINANCE32F_EXT:
      return GL_FLOAT;
    case GL_LUMINANCE_ALPHA32F_EXT:
      return GL_FLOAT;
    case GL_RGBA16F_EXT:
      return GL_HALF_FLOAT_OES;
    case GL_RGB16F_EXT:
      return GL_HALF_FLOAT_OES;
    case GL_ALPHA16F_EXT:
      return GL_HALF_FLOAT_OES;
    case GL_LUMINANCE16F_EXT:
      return GL_HALF_FLOAT_OES;
    case GL_LUMINANCE_ALPHA16F_EXT:
      return GL_HALF_FLOAT_OES;
    case GL_BGRA8_EXT:
      return GL_UNSIGNED_BYTE;
    default:
      return GL_NONE;
  }
}
