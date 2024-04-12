void WebPluginDelegateProxy::SetFocus(bool focused) {
  Send(new PluginMsg_SetFocus(instance_id_, focused));
#if defined(OS_WIN)
  if (render_view_)
    render_view_->PluginFocusChanged(focused, instance_id_);
#endif
}
