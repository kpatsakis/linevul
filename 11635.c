net::BackoffEntry* DataReductionProxyConfigServiceClient::GetBackoffEntry() {
  DCHECK(thread_checker_.CalledOnValidThread());
  return &backoff_entry_;
}
