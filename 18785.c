void LoadingDataCollector::RecordResourceLoadComplete(
    const NavigationID& navigation_id,
    const content::mojom::ResourceLoadInfo& resource_load_info) {
  auto nav_it = inflight_navigations_.find(navigation_id);
  if (nav_it == inflight_navigations_.end())
    return;

  if (!ShouldRecordResourceLoad(navigation_id, resource_load_info))
    return;

  auto& page_request_summary = *nav_it->second;
  page_request_summary.UpdateOrAddToOrigins(resource_load_info);
}
