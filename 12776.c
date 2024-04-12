void SessionService::Init() {
  registrar_.Add(this, content::NOTIFICATION_TAB_PARENTED,
                 content::NotificationService::AllSources());
  registrar_.Add(this, content::NOTIFICATION_TAB_CLOSED,
                 content::NotificationService::AllSources());
  registrar_.Add(this, content::NOTIFICATION_NAV_LIST_PRUNED,
                 content::NotificationService::AllSources());
  registrar_.Add(this, content::NOTIFICATION_NAV_ENTRY_CHANGED,
                 content::NotificationService::AllSources());
  registrar_.Add(this, content::NOTIFICATION_NAV_ENTRY_COMMITTED,
                 content::NotificationService::AllSources());
  registrar_.Add(this, chrome::NOTIFICATION_BROWSER_OPENED,
                 content::NotificationService::AllBrowserContextsAndSources());
  registrar_.Add(
      this, chrome::NOTIFICATION_TAB_CONTENTS_APPLICATION_EXTENSION_CHANGED,
      content::NotificationService::AllSources());
}
