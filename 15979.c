void ResourceFetcher::ClearPreloads(ClearPreloadsPolicy policy) {
  LogPreloadStats(policy);

  Vector<PreloadKey> keys_to_be_removed;
  for (const auto& pair : preloads_) {
    Resource* resource = pair.value;
    if (policy == kClearAllPreloads || !resource->IsLinkPreload()) {
      GetMemoryCache()->Remove(resource);
      keys_to_be_removed.push_back(pair.key);
    }
  }
  preloads_.RemoveAll(keys_to_be_removed);

  matched_preloads_.clear();
}
