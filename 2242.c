void WebPluginDelegateProxy::OnAcceleratedSurfaceBuffersSwapped(
    gfx::PluginWindowHandle window) {
  if (render_view_)
    render_view_->AcceleratedSurfaceBuffersSwapped(window);
}
