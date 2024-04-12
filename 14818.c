bool SyncBackendHost::HasUnsyncedItems() const {
  DCHECK(syncapi_initialized_);
  return core_->syncapi()->HasUnsyncedItems();
}
