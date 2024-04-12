void RenderViewHostImpl::OnFrameTreeUpdated(const std::string& frame_tree) {
  DCHECK(false);
  frame_tree_ = frame_tree;
  delegate_->DidUpdateFrameTree(this);
}
