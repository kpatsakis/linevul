char16_t* utf8_to_utf16_no_null_terminator(const uint8_t* u8str, size_t u8len, char16_t* u16str)
{
 const uint8_t* const u8end = u8str + u8len;
 const uint8_t* u8cur = u8str;
 char16_t* u16cur = u16str;

 while (u8cur < u8end) {
 size_t u8len = utf8_codepoint_len(*u8cur);
 uint32_t codepoint = utf8_to_utf32_codepoint(u8cur, u8len);

 if (codepoint <= 0xFFFF) {
 *u16cur++ = (char16_t) codepoint;
 } else {
            codepoint = codepoint - 0x10000;
 *u16cur++ = (char16_t) ((codepoint >> 10) + 0xD800);
 *u16cur++ = (char16_t) ((codepoint & 0x3FF) + 0xDC00);
 }

        u8cur += u8len;
 }
 return u16cur;
}
