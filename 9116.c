void TestingAutomationProvider::WaitForNavigation(int handle,
                                                  int64 last_navigation_time,
                                                  IPC::Message* reply_message) {
  NavigationController* controller = tab_tracker_->GetResource(handle);
  base::Time time(tab_tracker_->GetLastNavigationTime(handle));

  if (time.ToInternalValue() > last_navigation_time || !controller) {
    AutomationMsg_WaitForNavigation::WriteReplyParams(reply_message,
        controller == NULL ? AUTOMATION_MSG_NAVIGATION_ERROR :
                             AUTOMATION_MSG_NAVIGATION_SUCCESS);
    Send(reply_message);
    return;
  }

  new NavigationNotificationObserver(
      controller, this, reply_message, 1, true, false);
}
