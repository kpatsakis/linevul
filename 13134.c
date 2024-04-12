void AppListSyncableService::TrackUninstalledDriveApp(
    const std::string& drive_app_id) {
  const std::string sync_id = GetDriveAppSyncId(drive_app_id);
  SyncItem* sync_item = FindSyncItem(sync_id);
  if (sync_item) {
    DCHECK_EQ(sync_item->item_type,
              sync_pb::AppListSpecifics::TYPE_REMOVE_DEFAULT_APP);
    return;
  }

  sync_item = CreateSyncItem(
      sync_id, sync_pb::AppListSpecifics::TYPE_REMOVE_DEFAULT_APP);
  SendSyncChange(sync_item, SyncChange::ACTION_ADD);
}
