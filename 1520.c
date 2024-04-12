void HttpResponseHeaders::AddNonCacheableHeaders(HeaderSet* result) const {
  const std::string kCacheControl = "cache-control";
  const std::string kPrefix = "no-cache=\"";
  std::string value;
  void* iter = NULL;
  while (EnumerateHeader(&iter, kCacheControl, &value)) {
    if (value.size() > kPrefix.size() &&
        value.compare(0, kPrefix.size(), kPrefix) == 0) {
      if (value[value.size()-1] != '\"')
        continue;

      size_t len = value.size() - kPrefix.size() - 1;
      TrimString(value.substr(kPrefix.size(), len), HTTP_LWS, &value);

      size_t begin_pos = 0;
      for (;;) {
        size_t comma_pos = value.find(',', begin_pos);
        if (comma_pos == std::string::npos)
          comma_pos = value.size();
        size_t end = comma_pos;
        while (end > begin_pos && strchr(HTTP_LWS, value[end - 1]))
          end--;

        if (end > begin_pos) {
          std::string name = value.substr(begin_pos, end - begin_pos);
          StringToLowerASCII(&name);
          result->insert(name);
        }

        begin_pos = comma_pos + 1;
        while (begin_pos < value.size() && strchr(HTTP_LWS, value[begin_pos]))
          begin_pos++;
        if (begin_pos >= value.size())
          break;
      }
    }
  }
}
