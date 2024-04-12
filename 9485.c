const char *str8(const uint16_t *x, size_t x_len)
{
 static char buf[128];
 size_t max = 127;
 char *p = buf;

 if (x_len < max) {
        max = x_len;
 }

 if (x) {
 while ((max > 0) && (*x != '\0')) {
 *p++ = *x++;
            max--;
 }
 }
 *p++ = 0;
 return buf;
}
