void AppListSyncableService::AddOrUpdateFromSyncItem(AppListItem* app_item) {
  if (app_item->id() == kOemFolderId)
    return;

  SyncItem* sync_item = FindSyncItem(app_item->id());
  if (sync_item) {
    UpdateAppItemFromSyncItem(sync_item, app_item);
    return;
  }
  CreateSyncItemFromAppItem(app_item);
}
