void RenderViewImpl::OnPluginActionAt(const gfx::Point& location,
                                      const WebPluginAction& action) {
  if (webview())
    webview()->PerformPluginAction(action, location);
}
