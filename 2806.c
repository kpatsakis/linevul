WebGLImageConversion::DataFormat GetDataFormat(GLenum destination_format,
                                               GLenum destination_type) {
  WebGLImageConversion::DataFormat dst_format =
      WebGLImageConversion::kDataFormatRGBA8;
  switch (destination_type) {
    case GL_BYTE:
      switch (destination_format) {
        case GL_RED:
        case GL_RED_INTEGER:
          dst_format = WebGLImageConversion::kDataFormatR8_S;
          break;
        case GL_RG:
        case GL_RG_INTEGER:
          dst_format = WebGLImageConversion::kDataFormatRG8_S;
          break;
        case GL_RGB:
        case GL_RGB_INTEGER:
          dst_format = WebGLImageConversion::kDataFormatRGB8_S;
          break;
        case GL_RGBA:
        case GL_RGBA_INTEGER:
          dst_format = WebGLImageConversion::kDataFormatRGBA8_S;
          break;
        default:
          return WebGLImageConversion::kDataFormatNumFormats;
      }
      break;
    case GL_UNSIGNED_BYTE:
      switch (destination_format) {
        case GL_RGB:
        case GL_RGB_INTEGER:
        case GL_SRGB_EXT:
          dst_format = WebGLImageConversion::kDataFormatRGB8;
          break;
        case GL_RGBA:
        case GL_RGBA_INTEGER:
        case GL_SRGB_ALPHA_EXT:
          dst_format = WebGLImageConversion::kDataFormatRGBA8;
          break;
        case GL_ALPHA:
          dst_format = WebGLImageConversion::kDataFormatA8;
          break;
        case GL_LUMINANCE:
        case GL_RED:
        case GL_RED_INTEGER:
          dst_format = WebGLImageConversion::kDataFormatR8;
          break;
        case GL_RG:
        case GL_RG_INTEGER:
          dst_format = WebGLImageConversion::kDataFormatRG8;
          break;
        case GL_LUMINANCE_ALPHA:
          dst_format = WebGLImageConversion::kDataFormatRA8;
          break;
        default:
          return WebGLImageConversion::kDataFormatNumFormats;
      }
      break;
    case GL_SHORT:
      switch (destination_format) {
        case GL_RED_INTEGER:
          dst_format = WebGLImageConversion::kDataFormatR16_S;
          break;
        case GL_RG_INTEGER:
          dst_format = WebGLImageConversion::kDataFormatRG16_S;
          break;
        case GL_RGB_INTEGER:
          dst_format = WebGLImageConversion::kDataFormatRGB16_S;
        case GL_RGBA_INTEGER:
          dst_format = WebGLImageConversion::kDataFormatRGBA16_S;
        default:
          return WebGLImageConversion::kDataFormatNumFormats;
      }
      break;
    case GL_UNSIGNED_SHORT:
      switch (destination_format) {
        case GL_RED_INTEGER:
          dst_format = WebGLImageConversion::kDataFormatR16;
          break;
        case GL_DEPTH_COMPONENT:
          dst_format = WebGLImageConversion::kDataFormatD16;
          break;
        case GL_RG_INTEGER:
          dst_format = WebGLImageConversion::kDataFormatRG16;
          break;
        case GL_RGB_INTEGER:
          dst_format = WebGLImageConversion::kDataFormatRGB16;
          break;
        case GL_RGBA_INTEGER:
          dst_format = WebGLImageConversion::kDataFormatRGBA16;
          break;
        default:
          return WebGLImageConversion::kDataFormatNumFormats;
      }
      break;
    case GL_INT:
      switch (destination_format) {
        case GL_RED_INTEGER:
          dst_format = WebGLImageConversion::kDataFormatR32_S;
          break;
        case GL_RG_INTEGER:
          dst_format = WebGLImageConversion::kDataFormatRG32_S;
          break;
        case GL_RGB_INTEGER:
          dst_format = WebGLImageConversion::kDataFormatRGB32_S;
          break;
        case GL_RGBA_INTEGER:
          dst_format = WebGLImageConversion::kDataFormatRGBA32_S;
          break;
        default:
          return WebGLImageConversion::kDataFormatNumFormats;
      }
      break;
    case GL_UNSIGNED_INT:
      switch (destination_format) {
        case GL_RED_INTEGER:
          dst_format = WebGLImageConversion::kDataFormatR32;
          break;
        case GL_DEPTH_COMPONENT:
          dst_format = WebGLImageConversion::kDataFormatD32;
          break;
        case GL_RG_INTEGER:
          dst_format = WebGLImageConversion::kDataFormatRG32;
          break;
        case GL_RGB_INTEGER:
          dst_format = WebGLImageConversion::kDataFormatRGB32;
          break;
        case GL_RGBA_INTEGER:
          dst_format = WebGLImageConversion::kDataFormatRGBA32;
          break;
        default:
          return WebGLImageConversion::kDataFormatNumFormats;
      }
      break;
    case GL_HALF_FLOAT_OES:  // OES_texture_half_float
    case GL_HALF_FLOAT:
      switch (destination_format) {
        case GL_RGBA:
          dst_format = WebGLImageConversion::kDataFormatRGBA16F;
          break;
        case GL_RGB:
          dst_format = WebGLImageConversion::kDataFormatRGB16F;
          break;
        case GL_RG:
          dst_format = WebGLImageConversion::kDataFormatRG16F;
          break;
        case GL_ALPHA:
          dst_format = WebGLImageConversion::kDataFormatA16F;
          break;
        case GL_LUMINANCE:
        case GL_RED:
          dst_format = WebGLImageConversion::kDataFormatR16F;
          break;
        case GL_LUMINANCE_ALPHA:
          dst_format = WebGLImageConversion::kDataFormatRA16F;
          break;
        default:
          return WebGLImageConversion::kDataFormatNumFormats;
      }
      break;
    case GL_FLOAT:  // OES_texture_float
      switch (destination_format) {
        case GL_RGBA:
          dst_format = WebGLImageConversion::kDataFormatRGBA32F;
          break;
        case GL_RGB:
          dst_format = WebGLImageConversion::kDataFormatRGB32F;
          break;
        case GL_RG:
          dst_format = WebGLImageConversion::kDataFormatRG32F;
          break;
        case GL_ALPHA:
          dst_format = WebGLImageConversion::kDataFormatA32F;
          break;
        case GL_LUMINANCE:
        case GL_RED:
          dst_format = WebGLImageConversion::kDataFormatR32F;
          break;
        case GL_DEPTH_COMPONENT:
          dst_format = WebGLImageConversion::kDataFormatD32F;
          break;
        case GL_LUMINANCE_ALPHA:
          dst_format = WebGLImageConversion::kDataFormatRA32F;
          break;
        default:
          return WebGLImageConversion::kDataFormatNumFormats;
      }
      break;
    case GL_UNSIGNED_SHORT_4_4_4_4:
      dst_format = WebGLImageConversion::kDataFormatRGBA4444;
      break;
    case GL_UNSIGNED_SHORT_5_5_5_1:
      dst_format = WebGLImageConversion::kDataFormatRGBA5551;
      break;
    case GL_UNSIGNED_SHORT_5_6_5:
      dst_format = WebGLImageConversion::kDataFormatRGB565;
      break;
    case GL_UNSIGNED_INT_5_9_9_9_REV:
      dst_format = WebGLImageConversion::kDataFormatRGB5999;
      break;
    case GL_UNSIGNED_INT_24_8:
      dst_format = WebGLImageConversion::kDataFormatDS24_8;
      break;
    case GL_UNSIGNED_INT_10F_11F_11F_REV:
      dst_format = WebGLImageConversion::kDataFormatRGB10F11F11F;
      break;
    case GL_UNSIGNED_INT_2_10_10_10_REV:
      dst_format = WebGLImageConversion::kDataFormatRGBA2_10_10_10;
      break;
    default:
      return WebGLImageConversion::kDataFormatNumFormats;
  }
  return dst_format;
}
