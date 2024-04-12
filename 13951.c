void SyncBackendHost::Core::OnClearServerDataFailed() {
  host_->frontend_loop_->PostTask(FROM_HERE, NewRunnableMethod(this,
      &Core::HandleClearServerDataFailedOnFrontendLoop));
}
