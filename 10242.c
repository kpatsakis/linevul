static bool AdvanceToStartCode(const uint8_t* buffer,
                               int buffer_size,
                               int* offset,
                               int bytes_needed,
                               int num_bits,
                               uint32_t start_code) {
  DCHECK_GE(bytes_needed, 3);
  DCHECK_LE(num_bits, 24);  // Only supports up to 24 bits.

  uint32_t bits_to_shift = 24 - num_bits;
  uint32_t mask = (1 << num_bits) - 1;
  while (*offset + bytes_needed < buffer_size) {
    uint32_t next = Read24(buffer + *offset);
    if (((next >> bits_to_shift) & mask) == start_code)
      return true;
    ++(*offset);
  }
  return false;
}
