void RenderFrameImpl::SetCustomURLLoaderFactory(
    network::mojom::URLLoaderFactoryPtr factory) {
  GetLoaderFactoryBundle()->SetDefaultFactory(std::move(factory));
}
