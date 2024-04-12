GURL AppCache::GetNamespaceEntryUrl(
    const std::vector<AppCacheNamespace>& namespaces,
    const GURL& namespace_url) const {
  size_t count = namespaces.size();
  for (size_t i = 0; i < count; ++i) {
    if (namespaces[i].namespace_url == namespace_url)
      return namespaces[i].target_url;
  }
  NOTREACHED();
  return GURL();
}
