void AppCacheHost::OnUpdateComplete(AppCacheGroup* group) {
  DCHECK_EQ(group, group_being_updated_.get());
  group->RemoveUpdateObserver(this);

  SetSwappableCache(group);

  group_being_updated_ = NULL;
  newest_cache_of_group_being_updated_ = NULL;

  if (associated_cache_info_pending_ && associated_cache_.get() &&
      associated_cache_->is_complete()) {
    AppCacheInfo info;
    FillCacheInfo(
        associated_cache_.get(), preferred_manifest_url_, GetStatus(), &info);
    associated_cache_info_pending_ = false;
    frontend_->OnCacheSelected(host_id_, info);
  }
}
