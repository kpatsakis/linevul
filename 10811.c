static bool CheckSrt(const uint8* buffer, int buffer_size) {
  RCHECK(buffer_size > 20);

  int offset = StartsWith(buffer, buffer_size, UTF8_BYTE_ORDER_MARK) ? 3 : 0;
  RCHECK(VerifyNumber(buffer, buffer_size, &offset, 100));
  RCHECK(VerifyCharacters(buffer, buffer_size, &offset, '\n', '\r'));

  while (VerifyCharacters(buffer, buffer_size, &offset, '\n', '\r')) {}
  --offset;  // Since VerifyCharacters() gobbled up the next non-CR/LF.

  RCHECK(VerifyNumber(buffer, buffer_size, &offset, 100));
  RCHECK(VerifyCharacters(buffer, buffer_size, &offset, ':', 0));
  RCHECK(VerifyNumber(buffer, buffer_size, &offset, 2));
  RCHECK(VerifyCharacters(buffer, buffer_size, &offset, ':', 0));
  RCHECK(VerifyNumber(buffer, buffer_size, &offset, 2));
  RCHECK(VerifyCharacters(buffer, buffer_size, &offset, ',', '.'));
  RCHECK(VerifyNumber(buffer, buffer_size, &offset, 3));
  RCHECK(VerifyCharacters(buffer, buffer_size, &offset, ' ', 0));
  RCHECK(VerifyCharacters(buffer, buffer_size, &offset, '-', 0));
  RCHECK(VerifyCharacters(buffer, buffer_size, &offset, '-', 0));
  RCHECK(VerifyCharacters(buffer, buffer_size, &offset, '>', 0));
  RCHECK(VerifyCharacters(buffer, buffer_size, &offset, ' ', 0));
  RCHECK(VerifyNumber(buffer, buffer_size, &offset, 100));
  RCHECK(VerifyCharacters(buffer, buffer_size, &offset, ':', 0));
  RCHECK(VerifyNumber(buffer, buffer_size, &offset, 2));
  RCHECK(VerifyCharacters(buffer, buffer_size, &offset, ':', 0));
  RCHECK(VerifyNumber(buffer, buffer_size, &offset, 2));
  RCHECK(VerifyCharacters(buffer, buffer_size, &offset, ',', '.'));
  RCHECK(VerifyNumber(buffer, buffer_size, &offset, 3));
  return true;
}
