void RenderFrameImpl::BindNavigationClient(
    mojom::NavigationClientAssociatedRequest request) {
  navigation_client_impl_ = std::make_unique<NavigationClient>(this);
  navigation_client_impl_->Bind(std::move(request));
}
