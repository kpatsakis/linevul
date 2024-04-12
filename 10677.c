RenderFrameImpl::CreateApplicationCacheHost(
    blink::WebApplicationCacheHostClient* client) {
  if (!frame_ || !frame_->View())
    return nullptr;

  NavigationState* navigation_state = NavigationState::FromDocumentLoader(
      frame_->GetProvisionalDocumentLoader()
          ? frame_->GetProvisionalDocumentLoader()
          : frame_->GetDocumentLoader());

  return std::make_unique<RendererWebApplicationCacheHostImpl>(
      RenderViewImpl::FromWebView(frame_->View()), client,
      RenderThreadImpl::current()->appcache_dispatcher()->backend_proxy(),
      navigation_state->request_params().appcache_host_id, routing_id_);
}
