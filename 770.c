LocalFrame::PrefetchURLLoaderService() {
  if (!prefetch_loader_service_ &&
      base::FeatureList::IsEnabled(network::features::kNetworkService)) {
    GetInterfaceProvider().GetInterface(
        mojo::MakeRequest(&prefetch_loader_service_));
  }
  return prefetch_loader_service_.get();
}
