ResourceFetcher::DetermineRevalidationPolicyInternal(
    Resource::Type type,
    const FetchParameters& fetch_params,
    const Resource& existing_resource,
    bool is_static_data) const {
  const ResourceRequest& request = fetch_params.GetResourceRequest();

  if (IsDownloadOrStreamRequest(request))
    return kReload;

  if (IsImageResourceDisallowedToBeReused(existing_resource))
    return kReload;

  if (existing_resource.Loader() &&
      existing_resource.Loader()->Fetcher() != this) {
    return kReload;
  }

  if ((fetch_params.IsLinkPreload() || fetch_params.IsSpeculativePreload()) &&
      existing_resource.IsUnusedPreload()) {
    return kReload;
  }

  if (existing_resource.MustRefetchDueToIntegrityMetadata(fetch_params)) {
    return kReload;
  }

  if (existing_resource.GetType() != type) {
    RESOURCE_LOADING_DVLOG(1) << "ResourceFetcher::DetermineRevalidationPolicy "
                                 "reloading due to type mismatch.";
    return kReload;
  }

  if (is_static_data)
    return kUse;

  if (!existing_resource.CanReuse(fetch_params)) {
    RESOURCE_LOADING_DVLOG(1) << "ResourceFetcher::DetermineRevalidationPolicy "
                                 "reloading due to Resource::CanReuse() "
                                 "returning false.";
    return kReload;
  }

  if (allow_stale_resources_)
    return kUse;

  if (request.GetCachePolicy() == WebCachePolicy::kReturnCacheDataElseLoad)
    return kUse;

  if (existing_resource.HasCacheControlNoStoreHeader()) {
    RESOURCE_LOADING_DVLOG(1) << "ResourceFetcher::DetermineRevalidationPolicy "
                                 "reloading due to Cache-control: no-store.";
    return kReload;
  }

  if (type != Resource::kRaw) {
    if (!Context().IsLoadComplete() &&
        cached_resources_map_.Contains(
            MemoryCache::RemoveFragmentIdentifierIfNeeded(
                existing_resource.Url())))
      return kUse;
    if (existing_resource.IsLoading())
      return kUse;
  }

  if (request.GetCachePolicy() == WebCachePolicy::kBypassingCache) {
    RESOURCE_LOADING_DVLOG(1) << "ResourceFetcher::DetermineRevalidationPolicy "
                                 "reloading due to "
                                 "WebCachePolicy::BypassingCache.";
    return kReload;
  }

  if (existing_resource.ErrorOccurred()) {
    RESOURCE_LOADING_DVLOG(1) << "ResourceFetcher::DetermineRevalidationPolicy "
                                 "reloading due to resource being in the error "
                                 "state";
    return kReload;
  }

  if (type == Resource::kImage &&
      &existing_resource == CachedResource(request.Url())) {
    return kUse;
  }

  if (existing_resource.MustReloadDueToVaryHeader(request))
    return kReload;

  if (!existing_resource.CanReuseRedirectChain()) {
    RESOURCE_LOADING_DVLOG(1) << "ResourceFetcher::DetermineRevalidationPolicy "
                                 "reloading due to an uncacheable redirect";
    return kReload;
  }

  if (request.GetCachePolicy() == WebCachePolicy::kValidatingCacheData ||
      existing_resource.MustRevalidateDueToCacheHeaders() ||
      request.CacheControlContainsNoCache()) {
    if (existing_resource.IsUnusedPreload())
      return kReload;

    if (existing_resource.CanUseCacheValidator() &&
        !Context().IsControlledByServiceWorker()) {
      if (existing_resource.IsCacheValidator()) {
        DCHECK(existing_resource.StillNeedsLoad());
        return kUse;
      }
      return kRevalidate;
    }

    RESOURCE_LOADING_DVLOG(1) << "ResourceFetcher::DetermineRevalidationPolicy "
                                 "reloading due to missing cache validators.";
    return kReload;
  }

  return kUse;
}
