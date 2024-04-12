void LogBytes(const std::vector<CharType>& data, std::string* out) {
#if defined(OS_WIN)
  for (size_t i = 0; i < data.size(); ++i)
    out->push_back(data[i]);
#else
  static const size_t kMaxBytesToLog = 100;
  for (size_t i = 0; i < std::min(data.size(), kMaxBytesToLog); ++i) {
    if (isprint(data[i]))
      out->push_back(data[i]);
    else
      out->append(StringPrintf("[%02X]", static_cast<unsigned char>(data[i])));
  }
  if (data.size() > kMaxBytesToLog) {
    out->append(
        StringPrintf(" and %u more bytes",
                     static_cast<unsigned>(data.size() - kMaxBytesToLog)));
  }
#endif
}
