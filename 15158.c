void RenderFrameImpl::MarkInitiatorAsRequiringSeparateURLLoaderFactory(
    const url::Origin& initiator_origin,
    network::mojom::URLLoaderFactoryPtr url_loader_factory) {
  DCHECK(base::FeatureList::IsEnabled(network::features::kNetworkService));

  GetLoaderFactoryBundle();
  auto factory_bundle = std::make_unique<blink::URLLoaderFactoryBundleInfo>();
  factory_bundle->initiator_specific_factory_infos()[initiator_origin] =
      url_loader_factory.PassInterface();
  UpdateSubresourceLoaderFactories(std::move(factory_bundle));
}
