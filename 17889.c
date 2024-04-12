std::string SerializeOrigin(const url::Origin& origin) {
  return origin.GetURL().spec();
}
