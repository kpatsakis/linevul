bool GLES2Util::IsFloatFormat(uint32_t internal_format) {
  switch (internal_format) {
    case GL_R16F:
    case GL_R32F:
    case GL_RG16F:
    case GL_RG32F:
    case GL_R11F_G11F_B10F:
    case GL_RGB16F:
    case GL_RGB32F:
    case GL_RGBA16F:
    case GL_RGBA32F:
      return true;
    default:
      return false;
  }
}
