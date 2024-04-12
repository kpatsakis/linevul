KURL UrlWithoutFragment(const KURL& url) {
  KURL result = url;
  result.RemoveFragmentIdentifier();
  return result;
}
