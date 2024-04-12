bool ChromeContentBrowserClient::WillCreateURLLoaderFactory(
    content::BrowserContext* browser_context,
    content::RenderFrameHost* frame,
    bool is_navigation,
    const url::Origin& request_initiator,
    network::mojom::URLLoaderFactoryRequest* factory_request,
    bool* bypass_redirect_checks) {
  DCHECK(base::FeatureList::IsEnabled(network::features::kNetworkService));
  bool use_proxy = false;

#if BUILDFLAG(ENABLE_EXTENSIONS)
  auto* web_request_api =
      extensions::BrowserContextKeyedAPIFactory<extensions::WebRequestAPI>::Get(
          browser_context);

  if (web_request_api) {
    bool use_proxy_for_web_request =
        web_request_api->MaybeProxyURLLoaderFactory(frame, is_navigation,
                                                    factory_request);
    if (bypass_redirect_checks)
      *bypass_redirect_checks = use_proxy_for_web_request;
    use_proxy |= use_proxy_for_web_request;
  }
#endif

  use_proxy |= signin::ProxyingURLLoaderFactory::MaybeProxyRequest(
      frame, is_navigation, request_initiator, factory_request);

  return use_proxy;
}
