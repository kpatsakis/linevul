void OfflinePageModelImpl::ClearStorageIfNeeded(
    const ClearStorageCallback& callback) {
  if (!storage_manager_) {
    storage_manager_.reset(new OfflinePageStorageManager(
        this, GetPolicyController(), archive_manager_.get()));
  }
  storage_manager_->ClearPagesIfNeeded(callback);
}
