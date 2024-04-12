WebContentsImpl* WebContentsImpl::FromFrameTreeNode(
    FrameTreeNode* frame_tree_node) {
  return static_cast<WebContentsImpl*>(
      WebContents::FromRenderFrameHost(frame_tree_node->current_frame_host()));
}
