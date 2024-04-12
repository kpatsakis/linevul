std::vector<RenderFrameHost*> WebContentsImpl::GetAllFrames() {
  std::vector<RenderFrameHost*> frame_hosts;
  for (FrameTreeNode* node : frame_tree_.Nodes())
    frame_hosts.push_back(node->current_frame_host());
  return frame_hosts;
}
