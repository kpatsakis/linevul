AppCacheHost::~AppCacheHost() {
  service_->RemoveObserver(this);
  FOR_EACH_OBSERVER(Observer, observers_, OnDestructionImminent(this));
  if (associated_cache_.get())
    associated_cache_->UnassociateHost(this);
  if (group_being_updated_.get())
    group_being_updated_->RemoveUpdateObserver(this);
  storage()->CancelDelegateCallbacks(this);
  if (service()->quota_manager_proxy() && !origin_in_use_.is_empty())
    service()->quota_manager_proxy()->NotifyOriginNoLongerInUse(origin_in_use_);
}
