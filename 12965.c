void SyncManager::SyncInternal::CopyObservers(
    ObserverList<SyncManager::Observer>* observers_copy) {
  DCHECK_EQ(0U, observers_copy->size());
  base::AutoLock lock(observers_lock_);
  if (observers_.size() == 0)
    return;
  ObserverListBase<SyncManager::Observer>::Iterator it(observers_);
  SyncManager::Observer* obs;
  while ((obs = it.GetNext()) != NULL)
    observers_copy->AddObserver(obs);
}
