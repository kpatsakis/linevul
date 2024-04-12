void SyncBackendHost::HandleActionableErrorEventOnFrontendLoop(
    const browser_sync::SyncProtocolError& sync_error) {
  if (!frontend_)
    return;
  DCHECK_EQ(MessageLoop::current(), frontend_loop_);
  frontend_->OnActionableError(sync_error);
}
