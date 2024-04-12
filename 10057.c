void AppCacheHost::ObserveGroupBeingUpdated(AppCacheGroup* group) {
  DCHECK(!group_being_updated_.get());
  group_being_updated_ = group;
  newest_cache_of_group_being_updated_ = group->newest_complete_cache();
  group->AddUpdateObserver(this);
}
