void NewNotificationBalloonObserver::Observe(
    int type,
    const content::NotificationSource& source,
    const content::NotificationDetails& details) {
  if (automation_) {
    AutomationJSONReply(automation_,
                        reply_message_.release()).SendSuccess(NULL);
  }
  delete this;
}
