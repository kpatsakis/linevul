  std::string RequestString(const std::string& url,
                            const std::string& mode,
                            const std::string& credentials) const {
    return base::StringPrintf("url:%s, mode:%s, credentials:%s\n", url.c_str(),
                              mode.c_str(), credentials.c_str());
  }
