ResourceLoadPriority ResourceFetcher::ComputeLoadPriority(
    Resource::Type type,
    const ResourceRequest& resource_request,
    ResourcePriority::VisibilityStatus visibility,
    FetchParameters::DeferOption defer_option,
    FetchParameters::SpeculativePreloadType speculative_preload_type,
    bool is_link_preload) {
  ResourceLoadPriority priority = TypeToPriority(type);

  if (visibility == ResourcePriority::kVisible)
    priority = kResourceLoadPriorityHigh;

  if (type == Resource::kImage && !is_link_preload)
    image_fetched_ = true;

  if (type == Resource::kFont && is_link_preload)
    priority = kResourceLoadPriorityHigh;

  if (FetchParameters::kIdleLoad == defer_option) {
    priority = kResourceLoadPriorityVeryLow;
  } else if (type == Resource::kScript) {
    if (FetchParameters::kLazyLoad == defer_option) {
      priority = kResourceLoadPriorityLow;
    } else if (speculative_preload_type ==
                   FetchParameters::SpeculativePreloadType::kInDocument &&
               image_fetched_) {
      priority = kResourceLoadPriorityMedium;
    }
  } else if (FetchParameters::kLazyLoad == defer_option) {
    priority = kResourceLoadPriorityVeryLow;
  } else if (resource_request.GetRequestContext() ==
                 WebURLRequest::kRequestContextBeacon ||
             resource_request.GetRequestContext() ==
                 WebURLRequest::kRequestContextPing ||
             resource_request.GetRequestContext() ==
                 WebURLRequest::kRequestContextCSPReport) {
    priority = kResourceLoadPriorityVeryLow;
  }

  return std::max(priority, resource_request.Priority());
}
