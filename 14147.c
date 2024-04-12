static bool SniffForHTML(const char* content,
                         size_t size,
                         bool* have_enough_content,
                         std::string* result) {
  *have_enough_content &= TruncateSize(512, &size);

  const char* const end = content + size;
  const char* pos;
  for (pos = content; pos < end; ++pos) {
    if (!base::IsAsciiWhitespace(*pos))
      break;
  }
  return CheckForMagicNumbers(pos, end - pos, kSniffableTags,
                              arraysize(kSniffableTags), result);
}
