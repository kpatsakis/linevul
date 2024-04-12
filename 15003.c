bool TemplateURL::HasSearchTermsReplacementKey(const GURL& url) const {
  std::string params[] = {url.query(), url.ref()};

  for (int i = 0; i < 2; ++i) {
    url::Component query, key, value;
    query.len = static_cast<int>(params[i].size());
    while (url::ExtractQueryKeyValue(params[i].c_str(), &query, &key, &value)) {
      if (key.is_nonempty() &&
          params[i].substr(key.begin, key.len) ==
              search_terms_replacement_key()) {
        return true;
      }
    }
  }
  return false;
}
