HTMLCollection* Document::anchors() {
  return EnsureCachedCollection<HTMLCollection>(kDocAnchors);
}
