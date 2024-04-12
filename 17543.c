bool CanUseExistingResource(const net::HttpResponseInfo* http_info) {
  if (!http_info->headers || http_info->headers->RequiresValidation(
                                 http_info->request_time,
                                 http_info->response_time, base::Time::Now())) {
    return false;
  }

  std::string value;
  size_t iter = 0;
  while (http_info->headers->EnumerateHeader(&iter, "vary", &value)) {
    if (!base::EqualsCaseInsensitiveASCII(value, "Accept-Encoding") &&
        !base::EqualsCaseInsensitiveASCII(value, "Origin")) {
      return false;
    }
  }
  return true;
}
