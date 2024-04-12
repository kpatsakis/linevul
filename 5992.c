static bool CheckVC1(const uint8_t* buffer, int buffer_size) {

  RCHECK(buffer_size >= 24);

  if (buffer[0] == 0xc5 &&
      Read32(buffer + 4) == 0x04 &&
      Read32(buffer + 20) == 0x0c) {
    BitReader reader(buffer + 8, 12);

    int profile = ReadBits(&reader, 4);
    if (profile == 0 || profile == 4) {  // simple or main
      reader.SkipBits(3 + 5 + 1);

      RCHECK(ReadBits(&reader, 1) == 0);

      reader.SkipBits(1);

      RCHECK(ReadBits(&reader, 1) == 1);

      reader.SkipBits(1 + 1 + 2 + 1);

      RCHECK(ReadBits(&reader, 1) == 0);

      reader.SkipBits(1 + 1 + 1 + 3 + 2 + 1);

      RCHECK(ReadBits(&reader, 1) == 1);

    } else {
      RCHECK(profile == 12);  // Other profile values not allowed.
      RCHECK(ReadBits(&reader, 28) == 0);
    }

    RCHECK(ReadBits(&reader, 32) <= 8192);
    RCHECK(ReadBits(&reader, 32) <= 8192);
    return true;
  }

  int offset = 0;
  int sequence_start_code = 0;
  int frame_start_code = 0;
  while (true) {
    if (!AdvanceToStartCode(buffer, buffer_size, &offset, 5, 24, 1)) {
      return (sequence_start_code > 0 && frame_start_code > 0);
    }

    BitReader reader(buffer + offset, 5);
    RCHECK(ReadBits(&reader, 24) == 1);

    switch (ReadBits(&reader, 8)) {
      case VC1_SEQUENCE_START_CODE: {
        ++sequence_start_code;
        switch (ReadBits(&reader, 2)) {
          case 0:  // simple
          case 1:  // main
            RCHECK(ReadBits(&reader, 2) == 0);
            break;
          case 2:  // complex
            return false;
          case 3:  // advanced
            RCHECK(ReadBits(&reader, 3) <= 4);  // Verify level = 0..4
            RCHECK(ReadBits(&reader, 2) == 1);  // Verify colordiff_format = 1
            break;
        }
        break;
      }

      case VC1_ENTRY_POINT_START_CODE:
        RCHECK(sequence_start_code > 0);
        break;

      case VC1_FRAME_START_CODE:
        ++frame_start_code;
        break;
    }
    offset += 5;
  }
}
