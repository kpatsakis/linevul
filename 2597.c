void ShellAuraPlatformData::ResizeWindow(int width, int height) {
  root_window_->host()->SetBounds(gfx::Rect(width, height));
}
