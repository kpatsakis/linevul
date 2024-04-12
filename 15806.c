void RenderFrameHostImpl::OnDidStopLoading() {
  TRACE_EVENT1("navigation", "RenderFrameHostImpl::OnDidStopLoading",
               "frame_tree_node", frame_tree_node_->frame_tree_node_id());

  if (!is_loading_) {
    LOG(WARNING) << "OnDidStopLoading was called twice.";
    return;
  }

  is_loading_ = false;
  navigation_request_.reset();

  if (is_active())
    frame_tree_node_->DidStopLoading();
}
