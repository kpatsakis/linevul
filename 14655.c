void WebGL2RenderingContextBase::texImage3D(GLenum target,
                                            GLint level,
                                            GLint internalformat,
                                            GLsizei width,
                                            GLsizei height,
                                            GLsizei depth,
                                            GLint border,
                                            GLenum format,
                                            GLenum type,
                                            ImageData* pixels) {
  DCHECK(pixels);
  IntRect source_image_rect;
  source_image_rect.SetLocation(
      IntPoint(unpack_skip_pixels_, unpack_skip_rows_));
  source_image_rect.SetSize(IntSize(width, height));
  TexImageHelperImageData(kTexImage3D, target, level, internalformat, 0, format,
                          type, depth, 0, 0, 0, pixels, source_image_rect,
                          unpack_image_height_);
}
