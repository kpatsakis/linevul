void RenderFrameHostManager::EnsureRenderViewInitialized(
    RenderViewHostImpl* render_view_host,
    SiteInstance* instance) {
  DCHECK(frame_tree_node_->IsMainFrame());

  if (render_view_host->IsRenderViewLive())
    return;

  RenderFrameProxyHost* proxy = GetRenderFrameProxyHost(instance);
  if (!proxy)
    return;

  InitRenderView(render_view_host, proxy);
}
