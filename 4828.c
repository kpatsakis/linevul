WebURL BlinkTestRunner::RewriteLayoutTestsURL(const std::string& utf8_url) {
  const char kPrefix[] = "file:///tmp/LayoutTests/";
  const int kPrefixLen = arraysize(kPrefix) - 1;

  if (utf8_url.compare(0, kPrefixLen, kPrefix, kPrefixLen))
    return WebURL(GURL(utf8_url));

  base::FilePath replace_path =
      LayoutTestRenderProcessObserver::GetInstance()->webkit_source_dir()
          .Append(FILE_PATH_LITERAL("LayoutTests/"));
#if defined(OS_WIN)
  std::string utf8_path = base::WideToUTF8(replace_path.value());
#else
  std::string utf8_path =
      base::WideToUTF8(base::SysNativeMBToWide(replace_path.value()));
#endif
  std::string new_url =
      std::string("file://") + utf8_path + utf8_url.substr(kPrefixLen);
  return WebURL(GURL(new_url));
}
