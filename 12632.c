static bool CheckMJpeg(const uint8* buffer, int buffer_size) {
  RCHECK(buffer_size >= 16);

  int offset = 0;
  int last_restart = -1;
  int num_codes = 0;
  while (offset + 5 < buffer_size) {
    RCHECK(buffer[offset] == 0xff);
    uint8 code = buffer[offset + 1];
    RCHECK(code >= 0xc0 || code == 1);

    if (code == 0xff) {
      ++offset;
      continue;
    }

    if (code == 0xd9)
      return true;

    if (code == 0xd8 || code == 1) {
      offset += 2;
    } else if (code >= 0xd0 && code <= 0xd7) {
      int restart = code & 0x07;
      if (last_restart >= 0)
        RCHECK(restart == (last_restart + 1) % 8);
      last_restart = restart;
      offset += 2;
    } else {
      int length = Read16(buffer + offset + 2) + 2;

      if (code == 0xda) {
        int number_components = buffer[offset + 4];
        RCHECK(length == 8 + 2 * number_components);

        offset += length;
        while (offset + 2 < buffer_size) {
          if (buffer[offset] == 0xff && buffer[offset + 1] != 0)
            break;
          ++offset;
        }
      } else {
        offset += length;
      }
    }
    ++num_codes;
  }
  return (num_codes > 1);
}
