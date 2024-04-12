void WebPluginDelegateProxy::DidFinishManualLoading() {
  Send(new PluginMsg_DidFinishManualLoading(instance_id_));
}
