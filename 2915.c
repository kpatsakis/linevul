StoragePartitionImpl::GetURLLoaderFactoryForBrowserProcessInternal() {
  if (url_loader_factory_for_browser_process_ &&
      !url_loader_factory_for_browser_process_.encountered_error() &&
      is_test_url_loader_factory_for_browser_process_ !=
          g_url_loader_factory_callback_for_test.Get().is_null()) {
    return url_loader_factory_for_browser_process_.get();
  }

  network::mojom::URLLoaderFactoryParamsPtr params =
      network::mojom::URLLoaderFactoryParams::New();
  params->process_id = network::mojom::kBrowserProcessId;
  params->is_corb_enabled = false;
  params->disable_web_security =
      base::CommandLine::ForCurrentProcess()->HasSwitch(
          switches::kDisableWebSecurity);
  if (g_url_loader_factory_callback_for_test.Get().is_null()) {
    auto request = mojo::MakeRequest(&url_loader_factory_for_browser_process_);
    GetNetworkContext()->CreateURLLoaderFactory(std::move(request),
                                                std::move(params));
    is_test_url_loader_factory_for_browser_process_ = false;
    return url_loader_factory_for_browser_process_.get();
  }

  network::mojom::URLLoaderFactoryPtr original_factory;
  GetNetworkContext()->CreateURLLoaderFactory(
      mojo::MakeRequest(&original_factory), std::move(params));
  url_loader_factory_for_browser_process_ =
      g_url_loader_factory_callback_for_test.Get().Run(
          std::move(original_factory));
  is_test_url_loader_factory_for_browser_process_ = true;
  return url_loader_factory_for_browser_process_.get();
}
