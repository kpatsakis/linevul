void VariationsService::StartGoogleUpdateRegistrySync() {
  DCHECK(thread_checker_.CalledOnValidThread());
  registry_syncer_.RequestRegistrySync();
}
