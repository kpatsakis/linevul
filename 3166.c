void DiceTurnSyncOnHelper::FinishSyncSetupAndDelete(
    LoginUIService::SyncConfirmationUIClosedResult result) {
  switch (result) {
    case LoginUIService::CONFIGURE_SYNC_FIRST:
      EnableUnifiedConsentIfNeeded();
      delegate_->ShowSyncSettings();
      break;
    case LoginUIService::SYNC_WITH_DEFAULT_SETTINGS: {
      browser_sync::ProfileSyncService* sync_service = GetProfileSyncService();
      if (sync_service) {
        sync_service->SetFirstSetupComplete();
        EnableUnifiedConsentIfNeeded();
      }
      break;
    }
    case LoginUIService::ABORT_SIGNIN:
      signin_manager_->SignOutAndKeepAllAccounts(
          signin_metrics::ABORT_SIGNIN,
          signin_metrics::SignoutDelete::IGNORE_METRIC);
      AbortAndDelete();
      return;
  }
  delete this;
}
