void NavigatorImpl::CancelNavigation(FrameTreeNode* frame_tree_node,
                                     bool inform_renderer) {
  CHECK(IsBrowserSideNavigationEnabled());
  frame_tree_node->ResetNavigationRequest(false, inform_renderer);
  if (frame_tree_node->IsMainFrame())
    navigation_data_.reset();
}
