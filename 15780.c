void RenderWidgetHostViewAura::UnlockMouse() {
  aura::RootWindow* root_window = window_->GetRootWindow();
  if (!mouse_locked_ || !root_window)
    return;

  mouse_locked_ = false;

  window_->ReleaseCapture();
  window_->MoveCursorTo(unlocked_mouse_position_);
  aura::client::CursorClient* cursor_client =
      aura::client::GetCursorClient(root_window);
  if (cursor_client)
    cursor_client->ShowCursor(true);
  if (aura::client::GetTooltipClient(root_window))
    aura::client::GetTooltipClient(root_window)->SetTooltipsEnabled(true);

  host_->LostMouseLock();
}
