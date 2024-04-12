void WebPluginDelegatePepper::StartFind(const std::string& search_text,
                                        bool case_sensitive,
                                        int identifier) {
  find_identifier_ = identifier;
  GetFindExtensions()->startFind(
      instance()->npp(), search_text.c_str(), case_sensitive);
}
