ssize_t utf8_to_utf16_length(const uint8_t* u8str, size_t u8len)
{
 const uint8_t* const u8end = u8str + u8len;
 const uint8_t* u8cur = u8str;

 /* Validate that the UTF-8 is the correct len */
 size_t u16measuredLen = 0;
 while (u8cur < u8end) {
        u16measuredLen++;
 int u8charLen = utf8_codepoint_len(*u8cur);
 uint32_t codepoint = utf8_to_utf32_codepoint(u8cur, u8charLen);
 if (codepoint > 0xFFFF) u16measuredLen++; // this will be a surrogate pair in utf16
        u8cur += u8charLen;
 }

 /**
     * Make sure that we ended where we thought we would and the output UTF-16
     * will be exactly how long we were told it would be.
     */
 if (u8cur != u8end) {
 return -1;
 }

 return u16measuredLen;
}
