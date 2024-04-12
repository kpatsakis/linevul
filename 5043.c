bool Browser::GetSavedMaximizedState() const {
  if (CommandLine::ForCurrentProcess()->HasSwitch(switches::kStartMaximized))
    return true;

  if (maximized_state_ == MAXIMIZED_STATE_MAXIMIZED)
    return true;
  if (maximized_state_ == MAXIMIZED_STATE_UNMAXIMIZED)
    return false;

  gfx::Rect restored_bounds;
  bool maximized = false;
  WindowSizer::GetBrowserWindowBounds(app_name_, restored_bounds, this,
                                      &restored_bounds, &maximized);
  return maximized;
}
