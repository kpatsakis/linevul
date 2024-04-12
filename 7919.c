size_t GLES2Util::CalcClearBufferivDataCount(int buffer) {
  switch (buffer) {
    case GL_COLOR:
      return 4;
    case GL_STENCIL:
      return 1;
    default:
      return 0;
  }
}
