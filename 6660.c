void RenderFrameImpl::SetPendingNavigationParams(
    scoped_ptr<NavigationParams> navigation_params) {
  pending_navigation_params_ = navigation_params.Pass();
}
