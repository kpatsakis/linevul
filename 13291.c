void RenderFrameDevToolsAgentHost::DisconnectWebContents() {
  navigation_handles_.clear();
  SetFrameTreeNode(nullptr);
  scoped_refptr<RenderFrameDevToolsAgentHost> protect(this);
  UpdateFrameHost(nullptr);
  for (DevToolsSession* session : sessions())
    session->ResumeSendingMessagesToAgent();
}
