void SyncBackendHost::Core::DoRequestConfig(
    const syncable::ModelTypeBitSet& added_types,
    sync_api::ConfigureReason reason) {
  syncapi_->RequestConfig(added_types, reason);
}
