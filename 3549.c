void WebPluginDelegateProxy::OnDeferResourceLoading(unsigned long resource_id,
                                                    bool defer) {
  plugin_->SetDeferResourceLoading(resource_id, defer);
}
