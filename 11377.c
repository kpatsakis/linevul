void DevToolsAgent::clearBrowserCache() {
  Send(new DevToolsHostMsg_ClearBrowserCache(routing_id()));
}
