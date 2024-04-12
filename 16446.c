bool ShouldEnableQuicProxiesForHttpsUrls(
    const VariationParameters& quic_trial_params) {
  return base::LowerCaseEqualsASCII(
      GetVariationParam(quic_trial_params,
                        "enable_quic_proxies_for_https_urls"),
      "true");
}
