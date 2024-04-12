size_t GLES2Util::RenderbufferBytesPerPixel(int format) {
  switch (format) {
    case GL_STENCIL_INDEX8:
      return 1;
    case GL_RGBA4:
    case GL_RGB565:
    case GL_RGB5_A1:
    case GL_DEPTH_COMPONENT16:
      return 2;
    case GL_RGB:
    case GL_RGBA:
    case GL_DEPTH24_STENCIL8_OES:
    case GL_RGB8_OES:
    case GL_RGBA8_OES:
    case GL_DEPTH_COMPONENT24_OES:
      return 4;
    default:
      return 0;
  }
}
