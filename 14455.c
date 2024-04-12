bool RenderFrameDevToolsAgentHost::ShouldAllowSession(
    DevToolsSession* session) {
  DevToolsManager* manager = DevToolsManager::GetInstance();
  if (manager->delegate() && frame_host_) {
    if (!manager->delegate()->AllowInspectingRenderFrameHost(frame_host_))
      return false;
  }
  const bool is_webui =
      frame_host_ && (frame_host_->web_ui() || frame_host_->pending_web_ui());
  if (!session->client()->MayAttachToRenderer(frame_host_, is_webui))
    return false;
  return true;
}
