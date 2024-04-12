void RenderFrameHostManager::SwapOutOldFrame(
    std::unique_ptr<RenderFrameHostImpl> old_render_frame_host) {
  TRACE_EVENT1("navigation", "RenderFrameHostManager::SwapOutOldFrame",
               "FrameTreeNode id", frame_tree_node_->frame_tree_node_id());

  old_render_frame_host->SuppressFurtherDialogs();

  delegate_->CancelModalDialogsForRenderManager();

  if (!old_render_frame_host->IsRenderFrameLive())
    return;

  RenderFrameProxyHost* proxy =
      CreateRenderFrameProxyHost(old_render_frame_host->GetSiteInstance(),
                                 old_render_frame_host->render_view_host());

  old_render_frame_host->SetNavigationHandle(nullptr);

  old_render_frame_host->SwapOut(proxy, true);

  proxy->set_render_frame_proxy_created(true);

  pending_delete_hosts_.push_back(std::move(old_render_frame_host));
}
