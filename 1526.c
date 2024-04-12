std::string ExtractResourceId(const GURL& url) {
  return net::UnescapeURLComponent(url.ExtractFileName(),
                                   net::UnescapeRule::URL_SPECIAL_CHARS);
}
