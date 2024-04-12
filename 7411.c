bool DocumentLoader::CheckOriginIsHttpOrHttps(const SecurityOrigin* origin) {
  return origin &&
         (origin->Protocol() == "http" || origin->Protocol() == "https");
}
