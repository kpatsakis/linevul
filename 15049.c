void RenderWidgetHostImpl::OnMsgUnlockMouse() {
  RejectMouseLockOrUnlockIfNecessary();
}
