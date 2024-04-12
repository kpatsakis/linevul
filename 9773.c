void Pack<WebGLImageConversion::kDataFormatRGBA4444,
          WebGLImageConversion::kAlphaDoUnmultiply,
          uint8_t,
          uint16_t>(const uint8_t* source,
                    uint16_t* destination,
                    unsigned pixels_per_row) {
  for (unsigned i = 0; i < pixels_per_row; ++i) {
    float scale_factor = source[3] ? 255.0f / source[3] : 1.0f;
    uint8_t source_r =
        static_cast<uint8_t>(static_cast<float>(source[0]) * scale_factor);
    uint8_t source_g =
        static_cast<uint8_t>(static_cast<float>(source[1]) * scale_factor);
    uint8_t source_b =
        static_cast<uint8_t>(static_cast<float>(source[2]) * scale_factor);
    *destination = (((source_r & 0xF0) << 8) | ((source_g & 0xF0) << 4) |
                    (source_b & 0xF0) | (source[3] >> 4));
    source += 4;
    destination += 1;
  }
}
