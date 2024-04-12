bool DataReductionProxySettings::IsConfiguredDataReductionProxy(
    const net::ProxyServer& proxy_server) const {
  if (proxy_server.is_direct() || !proxy_server.is_valid())
    return false;

  for (const auto& drp_proxy : configured_proxies_.GetAll()) {
    if (drp_proxy.host_port_pair().Equals(proxy_server.host_port_pair()))
      return true;
  }
  return false;
}
