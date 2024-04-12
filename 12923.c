void DataReductionProxySettings::ClearDataSavingStatistics(
    DataReductionProxySavingsClearedReason reason) {
  DCHECK(thread_checker_.CalledOnValidThread());
  DCHECK(data_reduction_proxy_service_->compression_stats());
  data_reduction_proxy_service_->compression_stats()->ClearDataSavingStatistics(
      reason);
}
