bool Browser::ShouldCloseWindow() {
  if (!CanCloseWithInProgressDownloads())
    return false;

  return unload_controller_->ShouldCloseWindow();
}
