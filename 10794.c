 void EnterpriseEnrollmentScreen::HandleAuthError(
    const GoogleServiceAuthError& error) {
  scoped_ptr<GaiaAuthFetcher> scoped_killer(auth_fetcher_.release());

  if (!is_showing_)
    return;

  switch (error.state()) {
    case GoogleServiceAuthError::CONNECTION_FAILED:
      UMA_HISTOGRAM_ENUMERATION(policy::kMetricEnrollment,
                                policy::kMetricEnrollmentNetworkFailed,
                                policy::kMetricEnrollmentSize);
      actor_->ShowNetworkEnrollmentError();
      return;
    case GoogleServiceAuthError::INVALID_GAIA_CREDENTIALS:
    case GoogleServiceAuthError::CAPTCHA_REQUIRED:
    case GoogleServiceAuthError::TWO_FACTOR:
    case GoogleServiceAuthError::SERVICE_UNAVAILABLE:
      UMA_HISTOGRAM_ENUMERATION(policy::kMetricEnrollment,
                                policy::kMetricEnrollmentLoginFailed,
                                policy::kMetricEnrollmentSize);
      actor_->ShowAuthError(error);
      return;
    case GoogleServiceAuthError::USER_NOT_SIGNED_UP:
    case GoogleServiceAuthError::ACCOUNT_DELETED:
    case GoogleServiceAuthError::ACCOUNT_DISABLED:
      UMA_HISTOGRAM_ENUMERATION(policy::kMetricEnrollment,
                                policy::kMetricEnrollmentNotSupported,
                                policy::kMetricEnrollmentSize);
      actor_->ShowAccountError();
      return;
    case GoogleServiceAuthError::NONE:
    case GoogleServiceAuthError::HOSTED_NOT_ALLOWED:
      NOTREACHED() << error.state();
    case GoogleServiceAuthError::REQUEST_CANCELED:
      LOG(ERROR) << "Unexpected GAIA auth error: " << error.state();
      UMA_HISTOGRAM_ENUMERATION(policy::kMetricEnrollment,
                                policy::kMetricEnrollmentNetworkFailed,
                                policy::kMetricEnrollmentSize);
      actor_->ShowFatalAuthError();
      return;
  }

  NOTREACHED() << error.state();
  UMA_HISTOGRAM_ENUMERATION(policy::kMetricEnrollment,
                            policy::kMetricEnrollmentOtherFailed,
                            policy::kMetricEnrollmentSize);
}
