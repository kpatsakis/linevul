TestDataReductionProxyConfig::GetInFlightWarmupProxyDetails() const {
  if (in_flight_warmup_proxy_details_)
    return in_flight_warmup_proxy_details_;
  return DataReductionProxyConfig::GetInFlightWarmupProxyDetails();
}
