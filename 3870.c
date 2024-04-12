void SyncBackendHost::Core::OnConnectionStatusChange(
    sync_api::ConnectionStatus status) {
  if (!sync_loop_)
    return;
  DCHECK_EQ(MessageLoop::current(), sync_loop_);
  host_.Call(
      FROM_HERE,
      &SyncBackendHost::HandleConnectionStatusChangeOnFrontendLoop, status);
}
