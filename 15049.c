void RenderWidgetHostImpl::OnMsgUnlockMouse() {
  RejectMouseLockOrUnlockIfNecessary();
}