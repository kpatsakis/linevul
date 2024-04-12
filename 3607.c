std::string BlinkTestRunner::PathToLocalResource(const std::string& resource) {
#if defined(OS_WIN)
  if (resource.find("/tmp/") == 0) {
    GURL base_url = net::FilePathToFileURL(test_config_.temp_path);
    return base_url.Resolve(resource.substr(strlen("/tmp/"))).spec();
  }
#endif

  std::string result = resource;
  while (base::StringToLowerASCII(result).find("file:////") == 0) {
    result = result.substr(0, strlen("file:///")) +
             result.substr(strlen("file:////"));
  }
  return RewriteLayoutTestsURL(result).spec();
}
