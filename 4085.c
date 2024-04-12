string16 PolicyStatusInfo::GetSourceTypeString(
    PolicySourceType source_type) {
  static const char* strings[] = { "user", "device", "undefined" };
  DCHECK(static_cast<size_t>(source_type) < arraysize(strings));
  return ASCIIToUTF16(strings[source_type]);
}
