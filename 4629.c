RenderFrameHostImpl::CreateInitiatorSpecificURLLoaderFactories(
    const base::flat_set<url::Origin>& initiator_origins) {
  URLLoaderFactoryBundleInfo::OriginMap result;
  for (const url::Origin& initiator : initiator_origins) {
    network::mojom::URLLoaderFactoryPtrInfo factory_info;
    CreateNetworkServiceDefaultFactoryAndObserve(
        initiator, mojo::MakeRequest(&factory_info));
    result[initiator] = std::move(factory_info);
  }
  return result;
}
