bool GLES2Util::IsUnsignedIntegerFormat(uint32_t internal_format) {
  switch (internal_format) {
    case GL_R8UI:
    case GL_R16UI:
    case GL_R32UI:
    case GL_RG8UI:
    case GL_RG16UI:
    case GL_RG32UI:
    case GL_RGB8UI:
    case GL_RGB16UI:
    case GL_RGB32UI:
    case GL_RGBA8UI:
    case GL_RGB10_A2UI:
    case GL_RGBA16UI:
    case GL_RGBA32UI:
      return true;
    default:
      return false;
  }
}
