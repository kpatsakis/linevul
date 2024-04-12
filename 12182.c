int RenderFrameHostImpl::GetProxyCount() {
  if (!IsCurrent())
    return 0;
  return frame_tree_node_->render_manager()->GetProxyCount();
}
