void WebContentsImpl::RenderWidgetGotFocus(
    RenderWidgetHostImpl* render_widget_host) {
  if (delegate_ && render_widget_host && delegate_->EmbedsFullscreenWidget() &&
      render_widget_host->GetView() == GetFullscreenRenderWidgetHostView()) {
    NotifyWebContentsFocused(render_widget_host);
  }
}
