void RenderWidgetHostImpl::CancelKeyboardLock() {
  if (delegate_)
    delegate_->CancelKeyboardLock(this);

  UnlockKeyboard();

  keyboard_lock_allowed_ = false;
  keyboard_lock_requested_ = false;
  keyboard_keys_to_lock_.reset();
}
