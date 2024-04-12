bool ProfileSyncService::IsSyncEnabledAndLoggedIn() {
  if (IsManaged() || sync_prefs_.IsStartSuppressed())
    return false;

  return !signin_->GetAuthenticatedUsername().empty();
}
