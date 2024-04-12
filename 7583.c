void RenderFrameHostManager::OnDidUpdateFrameOwnerProperties(
    const FrameOwnerProperties& properties) {
  if (!SiteIsolationPolicy::AreCrossProcessFramesPossible())
    return;

  CHECK(frame_tree_node_->parent());
  SiteInstance* parent_instance =
      frame_tree_node_->parent()->current_frame_host()->GetSiteInstance();

  if (render_frame_host_->GetSiteInstance() != parent_instance) {
    render_frame_host_->Send(new FrameMsg_SetFrameOwnerProperties(
        render_frame_host_->GetRoutingID(), properties));
  }

  for (const auto& pair : proxy_hosts_) {
    if (pair.second->GetSiteInstance() != parent_instance) {
      pair.second->Send(new FrameMsg_SetFrameOwnerProperties(
          pair.second->GetRoutingID(), properties));
    }
  }
}
