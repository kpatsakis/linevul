void ChromeContentBrowserClient::OnNetworkServiceDataUseUpdate(
    int32_t network_traffic_annotation_id_hash,
    int64_t recv_bytes,
    int64_t sent_bytes) {
  if (data_use_measurement::ChromeDataUseMeasurement::GetInstance()) {
    data_use_measurement::ChromeDataUseMeasurement::GetInstance()
        ->ReportNetworkServiceDataUse(network_traffic_annotation_id_hash,
                                      recv_bytes, sent_bytes);
  }
}
