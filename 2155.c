static bool CheckCaf(const uint8_t* buffer, int buffer_size) {
  RCHECK(buffer_size >= 52);
  BitReader reader(buffer, buffer_size);

  RCHECK(ReadBits(&reader, 32) == TAG('c', 'a', 'f', 'f'));

  RCHECK(ReadBits(&reader, 16) == 1);

  reader.SkipBits(16);

  RCHECK(ReadBits(&reader, 32) == TAG('d', 'e', 's', 'c'));
  RCHECK(ReadBits(&reader, 64) == 32);

  RCHECK(ReadBits(&reader, 64) != 0);

  RCHECK(ReadBits(&reader, 32) != 0);

  reader.SkipBits(32 + 32);

  RCHECK(ReadBits(&reader, 32) != 0);
  return true;
}
