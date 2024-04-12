void SSLManager::UpdateEntry(NavigationEntryImpl* entry) {
  if (!entry)
    return;

  SSLStatus original_ssl_status = entry->GetSSL();  // Copy!

  policy()->UpdateEntry(entry, controller_->web_contents());

  if (!entry->GetSSL().Equals(original_ssl_status)) {
    content::NotificationService::current()->Notify(
        content::NOTIFICATION_SSL_VISIBLE_STATE_CHANGED,
        content::Source<NavigationController>(controller_),
        content::NotificationService::NoDetails());
  }
}
