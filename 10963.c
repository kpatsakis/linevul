bool WebGLImageConversion::PackImageData(
    Image* image,
    const void* pixels,
    GLenum format,
    GLenum type,
    bool flip_y,
    AlphaOp alpha_op,
    DataFormat source_format,
    unsigned source_image_width,
    unsigned source_image_height,
    const IntRect& source_image_sub_rectangle,
    int depth,
    unsigned source_unpack_alignment,
    int unpack_image_height,
    Vector<uint8_t>& data) {
  if (!pixels)
    return false;

  unsigned packed_size;
  PixelStoreParams params;
  params.alignment = 1;
  if (ComputeImageSizeInBytes(format, type, source_image_sub_rectangle.Width(),
                              source_image_sub_rectangle.Height(), depth,
                              params, &packed_size, nullptr,
                              nullptr) != GL_NO_ERROR)
    return false;
  data.resize(packed_size);

  return PackPixels(reinterpret_cast<const uint8_t*>(pixels), source_format,
                    source_image_width, source_image_height,
                    source_image_sub_rectangle, depth, source_unpack_alignment,
                    unpack_image_height, format, type, alpha_op, data.data(),
                    flip_y);
}
