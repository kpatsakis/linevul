void SyncBackendHost::HandleConnectionStatusChangeOnFrontendLoop(
    sync_api::ConnectionStatus status) {
  if (!frontend_)
    return;

  DCHECK_EQ(MessageLoop::current(), frontend_loop_);

  frontend_->OnConnectionStatusChange(status);
}
