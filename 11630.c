void DataReductionProxyConfig::OnRTTOrThroughputEstimatesComputed(
    base::TimeDelta http_rtt) {
  DCHECK(thread_checker_.CalledOnValidThread());
  http_rtt_ = http_rtt;
}
