DataReductionProxyConfig::GetProxyConnectionToProbe() const {
  DCHECK(thread_checker_.CalledOnValidThread());

  const std::vector<DataReductionProxyServer>& proxies =
      DataReductionProxyConfig::GetProxiesForHttp();

  for (const DataReductionProxyServer& proxy_server : proxies) {
    bool is_secure_proxy = proxy_server.IsSecureProxy();
    bool is_core_proxy = proxy_server.IsCoreProxy();
    if (!network_properties_manager_->HasWarmupURLProbeFailed(is_secure_proxy,
                                                              is_core_proxy) &&
        network_properties_manager_->ShouldFetchWarmupProbeURL(is_secure_proxy,
                                                               is_core_proxy)) {
      return proxy_server;
    }
  }

  for (const DataReductionProxyServer& proxy_server : proxies) {
    bool is_secure_proxy = proxy_server.IsSecureProxy();
    bool is_core_proxy = proxy_server.IsCoreProxy();
    if (network_properties_manager_->ShouldFetchWarmupProbeURL(is_secure_proxy,
                                                               is_core_proxy)) {
      return proxy_server;
    }
  }

  return base::nullopt;
}
