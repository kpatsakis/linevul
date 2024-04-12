static void ToColor_S32_Raw(SkColor dst[], const void* src, int width,
 SkColorTable*) {
 SkASSERT(width > 0);
 const SkPMColor* s = (const SkPMColor*)src;
 do {
 SkPMColor c = *s++;
 *dst++ = SkColorSetARGB(SkGetPackedA32(c), SkGetPackedR32(c),
 SkGetPackedG32(c), SkGetPackedB32(c));
 } while (--width != 0);
}
