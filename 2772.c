  void Initialize(const char* url,
                  bool expected,
                  size_t file_size = kFileSize) {
    InitializeWithCORS(url, expected, UrlData::CORS_UNSPECIFIED, file_size);
  }
