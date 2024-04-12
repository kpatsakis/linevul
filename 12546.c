char *itoa_r(intptr_t i, char *buf, size_t sz, int base, size_t padding) {
  size_t n = 1;
  if (n > sz)
    return NULL;

  if (base < 2 || base > 16) {
    buf[0] = '\000';
    return NULL;
  }

  char *start = buf;

  uintptr_t j = i;

  if (i < 0 && base == 10) {
    j = -i;

    if (++n > sz) {
      buf[0] = '\000';
      return NULL;
    }
    *start++ = '-';
  }

  char *ptr = start;
  do {
    if (++n > sz) {
      buf[0] = '\000';
      return NULL;
    }

    *ptr++ = "0123456789abcdef"[j % base];
    j /= base;

    if (padding > 0)
      padding--;
  } while (j > 0 || padding > 0);

  *ptr = '\000';

  while (--ptr > start) {
    char ch = *ptr;
    *ptr = *start;
    *start++ = ch;
  }
  return buf;
}
