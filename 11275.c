void RenderViewHostImpl::LostMouseLock() {
  RenderWidgetHostImpl::LostMouseLock();
  delegate_->LostMouseLock();
}
