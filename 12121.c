void WebPluginProxy::OnMissingPluginStatus(int status) {
  Send(new PluginHostMsg_MissingPluginStatus(route_id_, status));
}
