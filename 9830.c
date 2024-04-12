HTMLCollection* Document::forms() {
  return EnsureCachedCollection<HTMLCollection>(kDocForms);
}
