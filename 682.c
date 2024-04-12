size_t strnlen32(const char32_t *s, size_t maxlen)
{
 const char32_t *ss = s;
 while ((maxlen > 0) && *ss) {
    ss++;
    maxlen--;
 }
 return ss-s;
}
