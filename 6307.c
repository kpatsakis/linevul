bool WebContentsImpl::IsWidgetForMainFrame(
    RenderWidgetHostImpl* render_widget_host) {
  return render_widget_host == GetMainFrame()->GetRenderWidgetHost();
}
