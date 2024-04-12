void WebPluginDelegateProxy::OnMissingPluginStatus(int status) {
  if (render_view_)
    render_view_->OnMissingPluginStatus(this, status);
}
