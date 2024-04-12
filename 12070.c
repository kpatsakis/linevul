void UrlFetcher::Core::SetHeader(const std::string& key,
                                 const std::string& value) {
  request_headers_.SetHeader(key, value);
}
