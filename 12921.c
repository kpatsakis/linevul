uint32_t GetCompressedFormatRowPitch(const CompressedFormatInfo& info,
                                     uint32_t width) {
  uint32_t num_blocks_wide = (width + info.block_size - 1) / info.block_size;
  return num_blocks_wide * info.bytes_per_block;
}
