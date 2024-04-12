void RenderFrameHostImpl::OnFrameFocused() {
  frame_tree_->SetFocusedFrame(frame_tree_node_);
}
