    ~DataReductionProxyConfigServiceClient() {
  network_connection_tracker_->RemoveNetworkConnectionObserver(this);
}
