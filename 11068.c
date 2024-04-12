AppListSyncableService::CreateSyncItemFromAppItem(AppListItem* app_item) {
  sync_pb::AppListSpecifics::AppListItemType type;
  if (!GetAppListItemType(app_item, &type))
    return NULL;
  VLOG(2) << this << " CreateSyncItemFromAppItem:" << app_item->ToDebugString();
  SyncItem* sync_item = CreateSyncItem(app_item->id(), type);
  UpdateSyncItemFromAppItem(app_item, sync_item);
  SendSyncChange(sync_item, SyncChange::ACTION_ADD);
  return sync_item;
}
