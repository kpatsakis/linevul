void TerminateServiceWorkerOnIO(
    base::WeakPtr<ServiceWorkerContextCore> context_weak,
    int64_t version_id) {
  if (ServiceWorkerContextCore* context = context_weak.get()) {
    if (ServiceWorkerVersion* version = context->GetLiveVersion(version_id))
      version->StopWorker(base::DoNothing());
  }
}
