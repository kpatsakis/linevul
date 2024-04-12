void DiceTurnSyncOnHelper::SyncStartupCompleted() {
  DCHECK(sync_startup_tracker_);
  sync_startup_tracker_.reset();
  ShowSyncConfirmationUI();
}
