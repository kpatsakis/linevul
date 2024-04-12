bool LoadsFromCacheOnly(const ResourceRequest& request) {
  switch (request.GetCachePolicy()) {
    case WebCachePolicy::kUseProtocolCachePolicy:
    case WebCachePolicy::kValidatingCacheData:
    case WebCachePolicy::kBypassingCache:
    case WebCachePolicy::kReturnCacheDataElseLoad:
      return false;
    case WebCachePolicy::kReturnCacheDataDontLoad:
    case WebCachePolicy::kReturnCacheDataIfValid:
    case WebCachePolicy::kBypassCacheLoadOnlyFromCache:
      return true;
  }
  NOTREACHED();
  return false;
}
