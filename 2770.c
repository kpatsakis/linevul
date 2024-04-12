bool Extension::HasContentScriptAtURL(const GURL& url) const {
  for (UserScriptList::const_iterator it = content_scripts_.begin();
      it != content_scripts_.end(); ++it) {
    if (it->MatchesURL(url))
      return true;
  }
  return false;
}
