void AppCacheHost::GetResourceList(
    AppCacheResourceInfoVector* resource_infos) {
  if (associated_cache_.get() && associated_cache_->is_complete())
    associated_cache_->ToResourceInfoVector(resource_infos);
}
