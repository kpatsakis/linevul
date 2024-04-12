void RenderFrameImpl::DidUpdateCurrentHistoryItem() {
  render_view_->StartNavStateSyncTimerIfNecessary(this);
}
