RenderFrameHostImpl* WebContentsImpl::FindFrameByFrameTreeNodeId(
    int frame_tree_node_id) {
  FrameTreeNode* frame = frame_tree_.FindByID(frame_tree_node_id);
  return frame ? frame->current_frame_host() : nullptr;
}
