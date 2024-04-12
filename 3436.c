void AppCacheBackendImpl::GetResourceList(
    int host_id, std::vector<AppCacheResourceInfo>* resource_infos) {
  AppCacheHost* host = GetHost(host_id);
  if (!host)
    return;

  host->GetResourceList(resource_infos);
}
