bool IsURLAllowedInIncognito(const GURL& url) {
  return url.scheme() == chrome::kChromeUIScheme &&
      (url.host() == chrome::kChromeUISettingsHost ||
       url.host() == chrome::kChromeUIExtensionsHost ||
       url.host() == chrome::kChromeUIBookmarksHost);
}
