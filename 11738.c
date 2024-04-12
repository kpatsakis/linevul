void RenderWidgetHostViewAura::OnWindowDestroying() {
#if defined(OS_WIN)
  HWND parent = NULL;
  if (!window_->GetRootWindow() || host_->is_hidden()) {
    parent = ui::GetHiddenWindow();
  } else {
    parent = window_->GetRootWindow()->GetAcceleratedWidget();
  }
  LPARAM lparam = reinterpret_cast<LPARAM>(this);
  EnumChildWindows(parent, WindowDestroyingCallback, lparam);
#endif
}
