void ResourcePrefetchPredictor::Shutdown() {
  history_service_observer_.RemoveAll();
}
