void RenderFrameDevToolsAgentHost::UpdateFrameHost(
    RenderFrameHostImpl* frame_host) {
  if (frame_host == frame_host_) {
    if (frame_host && !render_frame_alive_) {
      render_frame_alive_ = true;
      for (auto* inspector : protocol::InspectorHandler::ForAgentHost(this))
        inspector->TargetReloadedAfterCrash();
      UpdateRendererChannel(IsAttached());
    }
    return;
  }

  if (frame_host && !ShouldCreateDevToolsForHost(frame_host)) {
    DestroyOnRenderFrameGone();
    return;
  }

  if (IsAttached())
    RevokePolicy();

  frame_host_ = frame_host;

  std::vector<DevToolsSession*> restricted_sessions;
  for (DevToolsSession* session : sessions()) {
    if (!ShouldAllowSession(session))
      restricted_sessions.push_back(session);
  }
  if (!restricted_sessions.empty())
    ForceDetachRestrictedSessions(restricted_sessions);

  if (!render_frame_alive_) {
    render_frame_alive_ = true;
    for (auto* inspector : protocol::InspectorHandler::ForAgentHost(this))
      inspector->TargetReloadedAfterCrash();
  }

  if (IsAttached())
    GrantPolicy();
  UpdateRendererChannel(IsAttached());
}
