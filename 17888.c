void HttpUtil::AppendHeaderIfMissing(const char* header_name,
                                     const std::string& header_value,
                                     std::string* headers) {
  if (header_value.empty())
    return;
  if (net::HttpUtil::HasHeader(*headers, header_name))
    return;
  *headers += std::string(header_name) + ": " + header_value + "\r\n";
}
