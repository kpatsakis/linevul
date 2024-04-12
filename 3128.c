inline uint32_t ReadUInt32(uint8_t* mem_bytes, int offset) {
  return
      static_cast<uint32_t>(mem_bytes[offset]) |
      (static_cast<uint32_t>(mem_bytes[offset + 1]) << 8) |
      (static_cast<uint32_t>(mem_bytes[offset + 2]) << 16) |
      (static_cast<uint32_t>(mem_bytes[offset + 3]) << 24);
}
