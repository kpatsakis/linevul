static bool SniffForInvalidOfficeDocs(const char* content,
                                      size_t size,
                                      const GURL& url,
                                      std::string* result) {
  if (!TruncateSize(kBytesRequiredForOfficeMagic, &size))
    return false;

  std::string office_version;
  if (!CheckForMagicNumbers(content, size, kOfficeMagicNumbers,
                            arraysize(kOfficeMagicNumbers), &office_version)) {
    *result = "application/octet-stream";
  }

  return true;
}
