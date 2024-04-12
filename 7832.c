static bool CheckH261(const uint8* buffer, int buffer_size) {
  RCHECK(buffer_size > 16);

  int offset = 0;
  bool seen_start_code = false;
  while (true) {
    if (!AdvanceToStartCode(buffer, buffer_size, &offset, 4, 20, 0x10)) {
      return seen_start_code;
    }

    BitReader reader(buffer + offset, buffer_size - offset);
    RCHECK(ReadBits(&reader, 20) == 0x10);

    reader.SkipBits(5 + 6);

    int extra = ReadBits(&reader, 1);
    while (extra == 1) {
      if (!reader.SkipBits(8))
        return seen_start_code;
      if (!reader.ReadBits(1, &extra))
        return seen_start_code;
    }

    int next;
    if (!reader.ReadBits(16, &next))
      return seen_start_code;
    RCHECK(next == 1);

    seen_start_code = true;
    offset += 4;
  }
}
