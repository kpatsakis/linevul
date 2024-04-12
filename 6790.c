void RenderWidgetHostViewAura::InternalSetBounds(const gfx::Rect& rect) {
  if (HasDisplayPropertyChanged(window_))
    host_->InvalidateScreenInfo();

  if (!in_bounds_changed_)
    window_->SetBounds(rect);
  host_->WasResized();
  MaybeCreateResizeLock();
  if (touch_editing_client_) {
    touch_editing_client_->OnSelectionOrCursorChanged(selection_anchor_rect_,
      selection_focus_rect_);
  }
#if defined(OS_WIN)
  if (!plugin_parent_window_ && GetNativeViewId()) {
    plugin_parent_window_ = ::CreateWindowEx(
        0, L"Static", NULL, WS_CHILDWINDOW, 0, 0, 0, 0,
        reinterpret_cast<HWND>(GetNativeViewId()), NULL, NULL, NULL);
    if (::IsWindow(plugin_parent_window_))
      ::SetProp(plugin_parent_window_, content::kPluginDummyParentProperty,
                reinterpret_cast<HANDLE>(true));
  }
  if (::IsWindow(plugin_parent_window_)) {
    gfx::Rect window_bounds = window_->GetBoundsInRootWindow();
    ::SetWindowPos(plugin_parent_window_, NULL, window_bounds.x(),
                   window_bounds.y(), window_bounds.width(),
                   window_bounds.height(), 0);
  }
#endif
}
