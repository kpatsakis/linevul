void SyncManager::SyncInternal::RaiseAuthNeededEvent() {
  ObserverList<SyncManager::Observer> temp_obs_list;
  CopyObservers(&temp_obs_list);
  FOR_EACH_OBSERVER(SyncManager::Observer, temp_obs_list,
      OnAuthError(AuthError(AuthError::INVALID_GAIA_CREDENTIALS)));
}
