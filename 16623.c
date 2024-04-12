DevToolsSession* DevToolsAgentHostImpl::SessionByClient(
    DevToolsAgentHostClient* client) {
  auto it = session_by_client_.find(client);
   return it == session_by_client_.end() ? nullptr : it->second.get();
 }
