void ProfileSyncService::TryStart() {
  if (!IsSyncEnabledAndLoggedIn())
    return;
  TokenService* token_service = TokenServiceFactory::GetForProfile(profile_);
  if (!token_service)
    return;
  if (IsSyncTokenAvailable() ||
      (!auto_start_enabled_ && token_service->TokensLoadedFromDB())) {
    if (HasSyncSetupCompleted() || auto_start_enabled_) {
      StartUp();
    }
  }
}
