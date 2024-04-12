bool IsStrongEtag(const std::string& etag) {
  return etag.size() > 2 && etag[0] == '"';
}
