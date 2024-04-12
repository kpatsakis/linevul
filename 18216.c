void SyncBackendHost::Core::DoShutdown(bool sync_disabled) {
  DCHECK(MessageLoop::current() == host_->core_thread_.message_loop());

  save_changes_timer_.Stop();
  syncapi_->Shutdown();  // Stops the SyncerThread.
  syncapi_->RemoveObserver(this);
  DisconnectChildJsEventRouter();
  host_->ui_worker()->OnSyncerShutdownComplete();

  if (sync_disabled)
    DeleteSyncDataFolder();

  host_ = NULL;
}
