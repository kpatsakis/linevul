bool PermissionsData::IsRuntimeBlockedHostUnsafe(const GURL& url) const {
  runtime_lock_.AssertAcquired();
  return PolicyBlockedHostsUnsafe().MatchesURL(url) &&
         !PolicyAllowedHostsUnsafe().MatchesURL(url);
}
