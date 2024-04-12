bool GetPacHttpsUrlStrippingEnabled() {
  network::mojom::NetworkContextParamsPtr network_context_params =
      g_browser_process->system_network_context_manager()
          ->CreateDefaultNetworkContextParams();
  return !network_context_params->dangerously_allow_pac_access_to_secure_urls;
}
