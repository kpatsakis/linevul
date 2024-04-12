static bool CheckH264(const uint8_t* buffer, int buffer_size) {
  RCHECK(buffer_size > 4);

  int offset = 0;
  int parameter_count = 0;
  while (true) {
    if (!AdvanceToStartCode(buffer, buffer_size, &offset, 4, 24, 1)) {
      return parameter_count > 0;
    }

    BitReader reader(buffer + offset, 4);
    RCHECK(ReadBits(&reader, 24) == 1);

    RCHECK(ReadBits(&reader, 1) == 0);

    int nal_ref_idc = ReadBits(&reader, 2);
    int nal_unit_type = ReadBits(&reader, 5);

    switch (nal_unit_type) {
      case 5:  // Coded slice of an IDR picture.
        RCHECK(nal_ref_idc != 0);
        break;
      case 6:   // Supplemental enhancement information (SEI).
      case 9:   // Access unit delimiter.
      case 10:  // End of sequence.
      case 11:  // End of stream.
      case 12:  // Filler data.
        RCHECK(nal_ref_idc == 0);
        break;
      case 7:  // Sequence parameter set.
      case 8:  // Picture parameter set.
        ++parameter_count;
        break;
    }

    offset += 4;
  }
}
