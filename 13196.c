bool ChildProcessSecurityPolicyImpl::CanRedirectToURL(const GURL& url) {
  if (!url.is_valid())
    return false;  // Can't redirect to invalid URLs.

  const std::string& scheme = url.scheme();

  if (scheme == kChromeErrorScheme)
    return false;

  if (IsPseudoScheme(scheme)) {
    return url.IsAboutBlank();
  }


  return true;
 }
