RenderFrameHostImpl* WebContentsImpl::FindFrameByFrameTreeNodeId(
    int frame_tree_node_id,
    int process_id) {
  FrameTreeNode* frame = frame_tree_.FindByID(frame_tree_node_id);

  if (!frame ||
      frame->current_frame_host()->GetProcess()->GetID() != process_id)
    return nullptr;

  return frame->current_frame_host();
}
