bool BrowserWindowGtk::IsActive() const {
  if (ui::ActiveWindowWatcherX::WMSupportsActivation())
    return is_active_;

  return gtk_window_is_active(window_);
}
