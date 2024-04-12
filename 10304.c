void SSLManager::NotifySSLInternalStateChanged(
    NavigationControllerImpl* controller) {
  content::NotificationService::current()->Notify(
      content::NOTIFICATION_SSL_INTERNAL_STATE_CHANGED,
      content::Source<content::BrowserContext>(controller->GetBrowserContext()),
      content::NotificationService::NoDetails());
}
