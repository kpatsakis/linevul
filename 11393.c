bool DesktopWindowTreeHostX11::HasCapture() const {
  return g_current_capture == this;
}
