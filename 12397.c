std::unique_ptr<RenderFrameHostImpl> RenderFrameHostManager::SetRenderFrameHost(
    std::unique_ptr<RenderFrameHostImpl> render_frame_host) {
  std::unique_ptr<RenderFrameHostImpl> old_render_frame_host =
      std::move(render_frame_host_);
  render_frame_host_ = std::move(render_frame_host);

  if (frame_tree_node_->IsMainFrame()) {
    if (render_frame_host_) {
      render_frame_host_->GetSiteInstance()->
          IncrementRelatedActiveContentsCount();
    }
    if (old_render_frame_host) {
      old_render_frame_host->GetSiteInstance()->
          DecrementRelatedActiveContentsCount();
    }
  }

  return old_render_frame_host;
}
