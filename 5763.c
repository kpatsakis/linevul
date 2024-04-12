void encodeBase64(
 const void *_data, size_t size, AString *out) {
    out->clear();

 const uint8_t *data = (const uint8_t *)_data;

 size_t i;
 for (i = 0; i < (size / 3) * 3; i += 3) {
 uint8_t x1 = data[i];
 uint8_t x2 = data[i + 1];
 uint8_t x3 = data[i + 2];

        out->append(encode6Bit(x1 >> 2));
        out->append(encode6Bit((x1 << 4 | x2 >> 4) & 0x3f));
        out->append(encode6Bit((x2 << 2 | x3 >> 6) & 0x3f));
        out->append(encode6Bit(x3 & 0x3f));
 }
 switch (size % 3) {
 case 0:
 break;
 case 2:
 {
 uint8_t x1 = data[i];
 uint8_t x2 = data[i + 1];
            out->append(encode6Bit(x1 >> 2));
            out->append(encode6Bit((x1 << 4 | x2 >> 4) & 0x3f));
            out->append(encode6Bit((x2 << 2) & 0x3f));
            out->append('=');
 break;
 }
 default:
 {
 uint8_t x1 = data[i];
            out->append(encode6Bit(x1 >> 2));
            out->append(encode6Bit((x1 << 4) & 0x3f));
            out->append("==");
 break;
 }
 }
}
