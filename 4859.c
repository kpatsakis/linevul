void ShellSurface::OnPreWindowStateTypeChange(
    ash::wm::WindowState* window_state,
    ash::wm::WindowStateType old_type) {
  ash::wm::WindowStateType new_type = window_state->GetStateType();
  if (ash::wm::IsMaximizedOrFullscreenOrPinnedWindowStateType(old_type) ||
      ash::wm::IsMaximizedOrFullscreenOrPinnedWindowStateType(new_type)) {
    if (configure_callback_.is_null())
      scoped_animations_disabled_.reset(new ScopedAnimationsDisabled(this));
  }
}
