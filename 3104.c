static bool SniffBinary(const char* content,
                        size_t size,
                        bool* have_enough_content,
                        std::string* result) {
  const bool is_truncated = TruncateSize(kMaxBytesToSniff, &size);

  std::string unused;
  if (CheckForMagicNumbers(content, size, kByteOrderMark,
                           arraysize(kByteOrderMark), &unused)) {
    result->assign("text/plain");
    return false;
  }

  if (LooksLikeBinary(content, size)) {
    result->assign("application/octet-stream");
    return true;
  }

  *have_enough_content &= is_truncated;
  result->assign("text/plain");
  return false;
}
