void RenderWidgetHostImpl::SendCursorVisibilityState(bool is_visible) {
  GetWidgetInputHandler()->CursorVisibilityChanged(is_visible);
}
