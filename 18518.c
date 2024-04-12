RenderFrameHostManager::~RenderFrameHostManager() {
  if (pending_render_frame_host_)
    UnsetPendingRenderFrameHost();

  if (speculative_render_frame_host_)
    UnsetSpeculativeRenderFrameHost();

  ResetProxyHosts();

  SetRenderFrameHost(std::unique_ptr<RenderFrameHostImpl>());
}
