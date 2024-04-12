static void WriteAlphaData(void* pixels,
                           uint32_t row_count,
                           uint32_t channel_count,
                           uint32_t alpha_channel_index,
                           uint32_t unpadded_row_size,
                           uint32_t padded_row_size,
                           pixel_data_type alpha_value) {
  DCHECK_GT(channel_count, 0U);
  DCHECK_EQ(unpadded_row_size % sizeof(pixel_data_type), 0U);
  uint32_t unpadded_row_size_in_elements =
      unpadded_row_size / sizeof(pixel_data_type);
  DCHECK_EQ(padded_row_size % sizeof(pixel_data_type), 0U);
  uint32_t padded_row_size_in_elements =
      padded_row_size / sizeof(pixel_data_type);
  pixel_data_type* dst =
      static_cast<pixel_data_type*>(pixels) + alpha_channel_index;
  for (uint32_t yy = 0; yy < row_count; ++yy) {
    pixel_data_type* end = dst + unpadded_row_size_in_elements;
    for (pixel_data_type* d = dst; d < end; d += channel_count) {
      *d = alpha_value;
    }
    dst += padded_row_size_in_elements;
  }
}
