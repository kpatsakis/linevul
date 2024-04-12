void WebGLRenderingContextBase::TexImageBitmapByGPU(
    ImageBitmap* bitmap,
    GLenum target,
    GLuint target_texture,
    bool flip_y,
    GLint xoffset,
    GLint yoffset,
    const IntRect& source_sub_rect) {
  bitmap->BitmapImage()->CopyToTexture(
      GetDrawingBuffer()->ContextProvider(), target, target_texture, flip_y,
      IntPoint(xoffset, yoffset), source_sub_rect);
}
