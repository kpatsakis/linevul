void DataReductionProxySettings::RecordDataReductionInit() const {
  DCHECK(thread_checker_.CalledOnValidThread());
  RecordStartupState(IsDataReductionProxyEnabled() ? PROXY_ENABLED
                                                   : PROXY_DISABLED);
  RecordStartupSavings();
}
