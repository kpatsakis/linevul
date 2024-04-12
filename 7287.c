void SyncBackendHost::Core::HandleStopSyncingPermanentlyOnFrontendLoop() {
  if (!host_ || !host_->frontend_)
    return;
  host_->frontend_->OnStopSyncingPermanently();
}
