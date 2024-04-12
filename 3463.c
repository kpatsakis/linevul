CreateDownloadURLLoaderFactoryGetter(StoragePartitionImpl* storage_partition,
                                     RenderFrameHost* rfh,
                                     bool is_download) {
  network::mojom::URLLoaderFactoryPtrInfo proxy_factory_ptr_info;
  network::mojom::URLLoaderFactoryRequest proxy_factory_request;
  if (rfh) {
    bool should_proxy = false;

    network::mojom::URLLoaderFactoryPtrInfo maybe_proxy_factory_ptr_info;
    network::mojom::URLLoaderFactoryRequest maybe_proxy_factory_request =
        MakeRequest(&maybe_proxy_factory_ptr_info);

    should_proxy = devtools_instrumentation::WillCreateURLLoaderFactory(
        static_cast<RenderFrameHostImpl*>(rfh), true, is_download,
        &maybe_proxy_factory_request);

    should_proxy |= GetContentClient()->browser()->WillCreateURLLoaderFactory(
        rfh->GetSiteInstance()->GetBrowserContext(), rfh,
        rfh->GetProcess()->GetID(), false /* is_navigation */,
        true /* is_download/ */, url::Origin(), &maybe_proxy_factory_request,
        nullptr /* header_client */, nullptr /* bypass_redirect_checks */);

    if (should_proxy) {
      proxy_factory_ptr_info = std::move(maybe_proxy_factory_ptr_info);
      proxy_factory_request = std::move(maybe_proxy_factory_request);
    }
  }

  return base::MakeRefCounted<NetworkDownloadURLLoaderFactoryGetter>(
      storage_partition->url_loader_factory_getter(),
      std::move(proxy_factory_ptr_info), std::move(proxy_factory_request));
}
