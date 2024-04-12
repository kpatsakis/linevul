static inline bool IsValidNameStart(UChar32 c) {
  if ((c >= 0x02BB && c <= 0x02C1) || c == 0x559 || c == 0x6E5 || c == 0x6E6)
    return true;

  if (c == ':' || c == '_')
    return true;

  const uint32_t kNameStartMask =
      WTF::unicode::kLetter_Lowercase | WTF::unicode::kLetter_Uppercase |
      WTF::unicode::kLetter_Other | WTF::unicode::kLetter_Titlecase |
      WTF::unicode::kNumber_Letter;
  if (!(WTF::unicode::Category(c) & kNameStartMask))
    return false;

  if (c >= 0xF900 && c < 0xFFFE)
    return false;

  WTF::unicode::CharDecompositionType decomp_type =
      WTF::unicode::DecompositionType(c);
  if (decomp_type == WTF::unicode::kDecompositionFont ||
      decomp_type == WTF::unicode::kDecompositionCompat)
    return false;

  return true;
}
