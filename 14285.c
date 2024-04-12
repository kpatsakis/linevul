void ProfileSyncService::Observe(int type,
                                 const content::NotificationSource& source,
                                 const content::NotificationDetails& details) {
  switch (type) {
    case chrome::NOTIFICATION_SYNC_CONFIGURE_START:
    case chrome::NOTIFICATION_SYNC_CONFIGURE_BLOCKED:
      NotifyObservers();
      break;
    case chrome::NOTIFICATION_SYNC_CONFIGURE_DONE: {
      DCHECK(cached_passphrase_.empty());

      DataTypeManager::ConfigureResult* result =
          content::Details<DataTypeManager::ConfigureResult>(details).ptr();

      configure_status_ = result->status;
      DVLOG(1) << "PSS SYNC_CONFIGURE_DONE called with status: "
               << configure_status_;


      if (configure_status_ == DataTypeManager::ABORTED &&
          expect_sync_configuration_aborted_) {
        DVLOG(0) << "ProfileSyncService::Observe Sync Configure aborted";
        expect_sync_configuration_aborted_ = false;
        return;
      }

      if (configure_status_ == DataTypeManager::RETRY) {
        OnSyncConfigureRetry();
        return;
      }

      if (configure_status_ != DataTypeManager::OK &&
          configure_status_ != DataTypeManager::PARTIAL_SUCCESS) {
        DCHECK_EQ(result->failed_data_types.size(),
                  static_cast<unsigned int>(1));
        SyncError error = result->failed_data_types.front();
        DCHECK(error.IsSet());
        std::string message =
          "Sync configuration failed with status " +
          DataTypeManager::ConfigureStatusToString(configure_status_) +
          " during " + syncable::ModelTypeToString(error.type()) +
          ": " + error.message();
        LOG(ERROR) << "ProfileSyncService error: "
                   << message;
        OnUnrecoverableError(error.location(), message);
        return;
      }

      MessageLoop::current()->PostTask(FROM_HERE,
          base::Bind(&ProfileSyncService::OnSyncConfigureDone,
                     weak_factory_.GetWeakPtr(), *result));

      DCHECK(!(IsPassphraseRequiredForDecryption() &&
               !IsEncryptedDatatypeEnabled()));

      if (encryption_pending_)
        backend_->EnableEncryptEverything();
      NotifyObservers();

      if (migrator_.get() &&
          migrator_->state() != browser_sync::BackendMigrator::IDLE) {
        migrator_->OnConfigureDone(*result);
      } else {
        StartSyncingWithServer();
      }

      break;
    }
    case chrome::NOTIFICATION_GOOGLE_SIGNIN_SUCCESSFUL: {
      const GoogleServiceSigninSuccessDetails* successful =
          content::Details<const GoogleServiceSigninSuccessDetails>(
              details).ptr();
      DCHECK(!successful->password.empty());
      if (!sync_prefs_.IsStartSuppressed()) {
        cached_passphrase_ = successful->password;
        ConsumeCachedPassphraseIfPossible();
      }
#if defined(OS_CHROMEOS)
      RefreshSpareBootstrapToken(successful->password);
#endif
      if (!sync_initialized() ||
          GetAuthError().state() != GoogleServiceAuthError::NONE) {
        is_auth_in_progress_ = true;
      }
      break;
    }
    case chrome::NOTIFICATION_TOKEN_REQUEST_FAILED: {
      const TokenService::TokenRequestFailedDetails& token_details =
          *(content::Details<const TokenService::TokenRequestFailedDetails>(
              details).ptr());
      if (IsTokenServiceRelevant(token_details.service()) &&
          !IsSyncTokenAvailable()) {
        GoogleServiceAuthError error(
            GoogleServiceAuthError::INVALID_GAIA_CREDENTIALS);
        UpdateAuthErrorState(error);
      }
      break;
    }
    case chrome::NOTIFICATION_TOKEN_AVAILABLE: {
      const TokenService::TokenAvailableDetails& token_details =
          *(content::Details<const TokenService::TokenAvailableDetails>(
              details).ptr());
      if (IsTokenServiceRelevant(token_details.service()) &&
          IsSyncEnabledAndLoggedIn() &&
          IsSyncTokenAvailable()) {
        if (backend_initialized_)
          backend_->UpdateCredentials(GetCredentials());
        else
          StartUp();
      }
      break;
    }
    case chrome::NOTIFICATION_TOKEN_LOADING_FINISHED: {
      if (IsSyncEnabledAndLoggedIn()) {
        if (auto_start_enabled_ && !IsSyncTokenAvailable())
          break;

        if (backend_initialized_)
          backend_->UpdateCredentials(GetCredentials());
        else
          StartUp();
      }
      break;
    }
    default: {
      NOTREACHED();
    }
  }
}
