void BrowserWindowGtk::UnMaximize() {
  gtk_window_util::UnMaximize(window_, bounds_, restored_bounds_);
}
