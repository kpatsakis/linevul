PendingNavigation::PendingNavigation(
    CommonNavigationParams common_params,
    mojom::BeginNavigationParamsPtr begin_navigation_params,
    scoped_refptr<network::SharedURLLoaderFactory> blob_url_loader_factory,
    mojom::NavigationClientAssociatedPtrInfo navigation_client,
    blink::mojom::NavigationInitiatorPtr navigation_initiator)
    : common_params(common_params),
      begin_navigation_params(std::move(begin_navigation_params)),
      blob_url_loader_factory(std::move(blob_url_loader_factory)),
      navigation_client(std::move(navigation_client)),
      navigation_initiator(std::move(navigation_initiator)) {}
