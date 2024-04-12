bool ChildProcessSecurityPolicyImpl::CanRequestURL(
    int child_id, const GURL& url) {
  if (!url.is_valid())
    return false;  // Can't request invalid URLs.

  const std::string& scheme = url.scheme();

  if (IsPseudoScheme(scheme))
    return url.IsAboutBlank() || url == kAboutSrcDocURL;

  if (url.SchemeIsBlob() || url.SchemeIsFileSystem()) {
    if (IsMalformedBlobUrl(url))
      return false;

    url::Origin origin = url::Origin::Create(url);
    return origin.unique() || CanRequestURL(child_id, GURL(origin.Serialize()));
  }

  if (IsWebSafeScheme(scheme))
    return true;

  {
    base::AutoLock lock(lock_);

    SecurityStateMap::iterator state = security_state_.find(child_id);
    if (state == security_state_.end())
      return false;

    if (state->second->CanRequestURL(url))
      return true;
  }

  return !GetContentClient()->browser()->IsHandledURL(url) &&
         !net::URLRequest::IsHandledURL(url);
}
