string16 IDNToUnicode(const std::string& host,
                      const std::string& languages) {
  return IDNToUnicodeWithOffsets(host, languages, NULL);
}
