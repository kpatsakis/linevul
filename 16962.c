void RenderWidgetHostImpl::SetPageFocus(bool focused) {
  is_focused_ = focused;

  if (!focused) {
    if (IsMouseLocked())
      view_->UnlockMouse();

    if (IsKeyboardLocked())
      UnlockKeyboard();

    if (auto* touch_emulator = GetExistingTouchEmulator())
      touch_emulator->CancelTouch();
  } else if (keyboard_lock_allowed_) {
    LockKeyboard();
  }

  GetWidgetInputHandler()->SetFocus(focused);

  if (RenderViewHost::From(this) && delegate_)
    delegate_->ReplicatePageFocus(focused);
}
