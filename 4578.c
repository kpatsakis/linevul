RenderFrameHostImpl::PassNavigationHandleOwnership() {
  DCHECK(!IsBrowserSideNavigationEnabled());
  if (navigation_handle_)
    navigation_handle_->set_is_transferring(true);
  return std::move(navigation_handle_);
}
