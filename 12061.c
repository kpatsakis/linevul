char16_t* utf8_to_utf16_n(const uint8_t* src, size_t srcLen, char16_t* dst, size_t dstLen) {
 const uint8_t* const u8end = src + srcLen;
 const uint8_t* u8cur = src;
 const char16_t* const u16end = dst + dstLen;
 char16_t* u16cur = dst;

 while (u8cur < u8end && u16cur < u16end) {
 size_t u8len = utf8_codepoint_len(*u8cur);
 uint32_t codepoint = utf8_to_utf32_codepoint(u8cur, u8len);

 if (codepoint <= 0xFFFF) {
 *u16cur++ = (char16_t) codepoint;
 } else {
            codepoint = codepoint - 0x10000;
 *u16cur++ = (char16_t) ((codepoint >> 10) + 0xD800);
 if (u16cur >= u16end) {
 return u16cur-1;
 }
 *u16cur++ = (char16_t) ((codepoint & 0x3FF) + 0xDC00);
 }

        u8cur += u8len;
 }
 return u16cur;
}
