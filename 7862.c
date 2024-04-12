void AppListSyncableService::RemoveItem(const std::string& id) {
  RemoveSyncItem(id);
  model_->DeleteItem(id);
  PruneEmptySyncFolders();
}
