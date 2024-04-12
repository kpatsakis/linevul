ash::wm::WindowState* ClientControlledShellSurface::GetWindowState() {
  return ash::wm::GetWindowState(widget_->GetNativeWindow());
}
