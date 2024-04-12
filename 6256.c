ExtensionResource Extension::GetIconResource(
    int size, ExtensionIconSet::MatchType match_type) const {
  std::string path = icons().Get(size, match_type);
  if (path.empty())
    return ExtensionResource();
  return GetResource(path);
}
