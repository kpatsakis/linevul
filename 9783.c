void Pack<WebGLImageConversion::kDataFormatRG32F,
          WebGLImageConversion::kAlphaDoNothing,
          float,
          float>(const float* source,
                 float* destination,
                 unsigned pixels_per_row) {
  for (unsigned i = 0; i < pixels_per_row; ++i) {
    destination[0] = source[0];
    destination[1] = source[1];
    source += 4;
    destination += 2;
  }
}
