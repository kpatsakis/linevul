void RenderFrameHostImpl::UpdateSubresourceLoaderFactories() {
  DCHECK(base::FeatureList::IsEnabled(network::features::kNetworkService));
  if (!has_committed_any_navigation_)
    return;
  DCHECK(!IsOutOfProcessNetworkService() ||
         network_service_connection_error_handler_holder_.is_bound());

  network::mojom::URLLoaderFactoryPtrInfo default_factory_info;
  bool bypass_redirect_checks = false;
  if (recreate_default_url_loader_factory_after_network_service_crash_) {
    bypass_redirect_checks = CreateNetworkServiceDefaultFactoryAndObserve(
        last_committed_origin_, mojo::MakeRequest(&default_factory_info));
  }

  std::unique_ptr<URLLoaderFactoryBundleInfo> subresource_loader_factories =
      std::make_unique<URLLoaderFactoryBundleInfo>(
          std::move(default_factory_info),
          URLLoaderFactoryBundleInfo::SchemeMap(),
          CreateInitiatorSpecificURLLoaderFactories(
              initiators_requiring_separate_url_loader_factory_),
          bypass_redirect_checks);
  GetNavigationControl()->UpdateSubresourceLoaderFactories(
      std::move(subresource_loader_factories));
}
