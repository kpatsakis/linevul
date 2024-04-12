int PluginResponseUtils::GetResponseInfo(
    const net::HttpResponseHeaders* response_headers,
    CPResponseInfoType type, void* buf, size_t buf_size) {
  if (!response_headers)
    return CPERR_FAILURE;

  switch (type) {
  case CPRESPONSEINFO_HTTP_STATUS:
    if (buf && buf_size) {
      int status = response_headers->response_code();
      memcpy(buf, &status, std::min(buf_size, sizeof(int)));
    }
    break;
  case CPRESPONSEINFO_HTTP_RAW_HEADERS: {
    const std::string& headers = response_headers->raw_headers();
    if (buf_size < headers.size()+1)
      return static_cast<int>(headers.size()+1);
    if (buf)
      memcpy(buf, headers.c_str(), headers.size()+1);
    break;
    }
  default:
    return CPERR_INVALID_VERSION;
  }

  return CPERR_SUCCESS;
}
