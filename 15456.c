bool ChromePasswordManagerClient::IsFillingEnabled(const GURL& url) const {
  const bool ssl_errors = net::IsCertStatusError(GetMainFrameCertStatus());

  if (log_manager_->IsLoggingActive()) {
    password_manager::BrowserSavePasswordProgressLogger logger(
        log_manager_.get());
    logger.LogBoolean(Logger::STRING_SSL_ERRORS_PRESENT, ssl_errors);
  }

  return !ssl_errors && IsPasswordManagementEnabledForCurrentPage(url);
}
