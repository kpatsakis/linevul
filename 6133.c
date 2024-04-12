DataReductionProxyConfig::~DataReductionProxyConfig() {
  network_connection_tracker_->RemoveNetworkConnectionObserver(this);
}
