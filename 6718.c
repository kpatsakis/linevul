void NavigationNotificationObserver::Observe(
    int type, const content::NotificationSource& source,
    const content::NotificationDetails& details) {
  if (!automation_) {
    delete this;
    return;
  }

  if (type == content::NOTIFICATION_NAV_ENTRY_COMMITTED ||
      type == content::NOTIFICATION_LOAD_START) {
    navigation_started_ = true;
  } else if (type == content::NOTIFICATION_LOAD_STOP) {
    if (navigation_started_) {
      navigation_started_ = false;
      if (--navigations_remaining_ == 0)
        ConditionMet(AUTOMATION_MSG_NAVIGATION_SUCCESS);
    }
  } else if (type == chrome::NOTIFICATION_AUTH_SUPPLIED ||
             type == chrome::NOTIFICATION_AUTH_CANCELLED) {
    navigation_started_ = true;
  } else if (type == chrome::NOTIFICATION_AUTH_NEEDED) {
    navigation_started_ = false;
    ConditionMet(AUTOMATION_MSG_NAVIGATION_AUTH_NEEDED);
  } else if (type == chrome::NOTIFICATION_APP_MODAL_DIALOG_SHOWN) {
    ConditionMet(AUTOMATION_MSG_NAVIGATION_BLOCKED_BY_MODAL_DIALOG);
  } else {
    NOTREACHED();
  }
}
