  std::string RegisterMockedHttpURLLoad(const std::string& file_name) {
    return URLTestHelpers::RegisterMockedURLLoadFromBase(
               WebString::FromUTF8(base_url_), testing::CoreTestDataPath(),
               WebString::FromUTF8(file_name))
        .GetString()
        .Utf8();
  }
