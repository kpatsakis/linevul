bool DesktopWindowTreeHostX11::IsVisible() const {
  return window_mapped_in_client_ || IsMinimized();
}
