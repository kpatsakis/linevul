void SyncBackendHost::Core::NotifyUpdatedToken(const std::string& token) {
  if (!host_)
    return;
  DCHECK(BrowserThread::CurrentlyOn(BrowserThread::UI));
  TokenAvailableDetails details(GaiaConstants::kSyncService, token);
  NotificationService::current()->Notify(
      chrome::NOTIFICATION_TOKEN_UPDATED,
      Source<Profile>(host_->profile_),
      Details<const TokenAvailableDetails>(&details));
}
