Resource* ResourceFetcher::MatchPreload(const FetchParameters& params,
                                        Resource::Type type) {
  auto it = preloads_.find(PreloadKey(params.Url(), type));
  if (it == preloads_.end())
    return nullptr;

  Resource* resource = it->value;

  if (resource->MustRefetchDueToIntegrityMetadata(params))
    return nullptr;

  if (params.IsSpeculativePreload())
    return resource;
  if (params.IsLinkPreload()) {
    resource->SetLinkPreload(true);
    return resource;
  }

  const ResourceRequest& request = params.GetResourceRequest();
  if (request.DownloadToFile())
    return nullptr;

  if (IsImageResourceDisallowedToBeReused(*resource) ||
      !resource->CanReuse(params))
    return nullptr;

  if (!resource->MatchPreload(params, Context().GetLoadingTaskRunner().get()))
    return nullptr;
  preloads_.erase(it);
  matched_preloads_.push_back(resource);
  return resource;
}
