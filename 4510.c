void AllViewsStoppedLoadingObserver::Observe(
    int type,
    const content::NotificationSource& source,
    const content::NotificationDetails& details) {
  if (!automation_) {
    delete this;
    return;
  }
  if (type == content::NOTIFICATION_LOAD_STOP) {
    CheckIfNoMorePendingLoads();
  } else if (type == chrome::NOTIFICATION_APP_MODAL_DIALOG_SHOWN) {
    AutomationJSONReply(automation_,
                        reply_message_.release()).SendSuccess(NULL);
    delete this;
  }
}
