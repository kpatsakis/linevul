bool Extension::CanSpecifyHostPermission(const URLPattern& pattern,
    const APIPermissionSet& permissions) const {
  if (!pattern.match_all_urls() &&
      pattern.MatchesScheme(chrome::kChromeUIScheme)) {
    if (pattern.host() == chrome::kChromeUIFaviconHost)
      return true;

    if (pattern.host() == chrome::kChromeUIThumbnailHost) {
      return permissions.find(APIPermission::kExperimental) !=
          permissions.end();
    }

    if (CanExecuteScriptEverywhere())
      return true;

    return false;
  }

  return true;
}
