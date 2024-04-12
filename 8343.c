static inline bool IsValidNamePart(UChar32 c) {
  if (IsValidNameStart(c))
    return true;

  if (c == 0x00B7 || c == 0x0387)
    return true;

  if (c == '-' || c == '.')
    return true;

  const uint32_t kOtherNamePartMask =
      WTF::Unicode::kMark_NonSpacing | WTF::Unicode::kMark_Enclosing |
      WTF::Unicode::kMark_SpacingCombining | WTF::Unicode::kLetter_Modifier |
      WTF::Unicode::kNumber_DecimalDigit;
  if (!(WTF::Unicode::Category(c) & kOtherNamePartMask))
    return false;

  if (c >= 0xF900 && c < 0xFFFE)
    return false;

  WTF::Unicode::CharDecompositionType decomp_type =
      WTF::Unicode::DecompositionType(c);
  if (decomp_type == WTF::Unicode::kDecompositionFont ||
      decomp_type == WTF::Unicode::kDecompositionCompat)
    return false;

  return true;
}
