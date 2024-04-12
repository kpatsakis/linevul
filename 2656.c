bool DesktopWindowTreeHostX11::IsActive() const {
  bool is_active =
      (has_window_focus_ || has_pointer_focus_) && !ignore_keyboard_input_;

  DCHECK(!is_active || window_mapped_in_server_);

  DCHECK(!has_window_focus_ || !has_pointer_focus_);

  return is_active;
}
