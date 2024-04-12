void WebContentsImpl::SetShowingContextMenu(bool showing) {
  DCHECK_NE(showing_context_menu_, showing);
  showing_context_menu_ = showing;

  if (auto* view = GetRenderWidgetHostView()) {
    static_cast<RenderWidgetHostViewBase*>(view)->SetShowingContextMenu(
        showing);
  }
}
