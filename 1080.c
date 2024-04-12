HTMLAllCollection* Document::all() {
  return EnsureCachedCollection<HTMLAllCollection>(kDocAll);
}
