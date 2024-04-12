void TabSpecificContentSettings::OnGeolocationPermissionSet(
    const GURL& requesting_origin,
    bool allowed) {
  geolocation_settings_state_.OnGeolocationPermissionSet(requesting_origin,
                                                         allowed);
  content::NotificationService::current()->Notify(
      chrome::NOTIFICATION_WEB_CONTENT_SETTINGS_CHANGED,
      content::Source<WebContents>(web_contents()),
      content::NotificationService::NoDetails());
}
