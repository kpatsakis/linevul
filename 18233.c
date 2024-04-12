ExtensionsUpdatedObserver::ExtensionsUpdatedObserver(
    ExtensionProcessManager* manager, AutomationProvider* automation,
    IPC::Message* reply_message)
    : manager_(manager), automation_(automation->AsWeakPtr()),
      reply_message_(reply_message), updater_finished_(false) {
  registrar_.Add(this, content::NOTIFICATION_LOAD_STOP,
                 content::NotificationService::AllSources());
  registrar_.Add(this, chrome::NOTIFICATION_EXTENSION_INSTALL_ERROR,
                 content::NotificationService::AllSources());
  registrar_.Add(this, chrome::NOTIFICATION_EXTENSION_INSTALL_NOT_ALLOWED,
                 content::NotificationService::AllSources());
  registrar_.Add(this, chrome::NOTIFICATION_EXTENSION_LOADED,
                 content::NotificationService::AllSources());
  registrar_.Add(this, chrome::NOTIFICATION_EXTENSION_UPDATE_DISABLED,
                 content::NotificationService::AllSources());
  registrar_.Add(this, chrome::NOTIFICATION_EXTENSION_UPDATE_FOUND,
                 content::NotificationService::AllSources());
  registrar_.Add(this, chrome::NOTIFICATION_EXTENSION_UPDATING_FINISHED,
                 content::NotificationService::AllSources());
}
