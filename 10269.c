static int GetElementId(BitReader* reader) {
  if (reader->bits_available() >= 8) {
    int num_bits_to_read = 0;
    static int prefix[] = { 0x80, 0x4000, 0x200000, 0x10000000 };
    for (int i = 0; i < 4; ++i) {
      num_bits_to_read += 7;
      if (ReadBits(reader, 1) == 1) {
        if (reader->bits_available() < num_bits_to_read)
          break;
        return ReadBits(reader, num_bits_to_read) | prefix[i];
      }
    }
  }
  return -1;
}
