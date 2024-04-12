static size_t q_encoder(char *str, const char *buf, size_t buflen, const char *tocode)
{
  static const char hex[] = "0123456789ABCDEF";
  char *s0 = str;

  memcpy(str, "=?", 2);
  str += 2;
  memcpy(str, tocode, strlen(tocode));
  str += strlen(tocode);
  memcpy(str, "?Q?", 3);
  str += 3;
  while (buflen--)
  {
    unsigned char c = *buf++;
    if (c == ' ')
      *str++ = '_';
    else if ((c >= 0x7f) || (c < 0x20) || (c == '_') || strchr(MimeSpecials, c))
    {
      *str++ = '=';
      *str++ = hex[(c & 0xf0) >> 4];
      *str++ = hex[c & 0x0f];
    }
    else
      *str++ = c;
  }
  memcpy(str, "?=", 2);
  str += 2;
  return (str - s0);
}
