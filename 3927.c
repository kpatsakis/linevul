void WebContentsImpl::CancelKeyboardLock(
    RenderWidgetHostImpl* render_widget_host) {
  if (!keyboard_lock_widget_ || render_widget_host != keyboard_lock_widget_)
    return;

  RenderWidgetHostImpl* old_keyboard_lock_widget = keyboard_lock_widget_;
  keyboard_lock_widget_ = nullptr;

  if (delegate_)
    delegate_->CancelKeyboardLockRequest(this);

  old_keyboard_lock_widget->CancelKeyboardLock();
}
