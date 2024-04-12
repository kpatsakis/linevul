void AutofillDownloadManager::SetObserver(
    AutofillDownloadManager::Observer *observer) {
  if (observer) {
    DCHECK(!observer_);
    observer_ = observer;
  } else {
    observer_ = NULL;
  }
}
