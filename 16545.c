void WebPluginDelegateProxy::PluginDestroyed() {
#if defined(OS_MACOSX) || defined(OS_WIN)
  if (render_view_)
    render_view_->PluginFocusChanged(false, instance_id_);
#endif

  if (window_)
    WillDestroyWindow();

  if (render_view_)
    render_view_->UnregisterPluginDelegate(this);

  if (channel_host_) {
    Send(new PluginMsg_DestroyInstance(instance_id_));

    channel_host_->RemoveRoute(instance_id_);

    channel_host_ = NULL;
  }

  if (window_script_object_) {
    window_script_object_->DeleteSoon();
  }

  plugin_ = NULL;

  MessageLoop::current()->DeleteSoon(FROM_HERE, this);
}
