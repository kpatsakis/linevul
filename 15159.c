void Pack<WebGLImageConversion::kDataFormatRGB16F,
          WebGLImageConversion::kAlphaDoNothing,
          float,
          uint16_t>(const float* source,
                    uint16_t* destination,
                    unsigned pixels_per_row) {
  for (unsigned i = 0; i < pixels_per_row; ++i) {
    destination[0] = ConvertFloatToHalfFloat(source[0]);
    destination[1] = ConvertFloatToHalfFloat(source[1]);
    destination[2] = ConvertFloatToHalfFloat(source[2]);
    source += 4;
    destination += 3;
  }
}
