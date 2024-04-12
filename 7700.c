void NewTabObserver::Observe(int type,
                             const content::NotificationSource& source,
                             const content::NotificationDetails& details) {
  DCHECK_EQ(chrome::NOTIFICATION_TAB_PARENTED, type);
  NavigationController* controller =
      &(content::Source<content::WebContents>(source).ptr()->GetController());
  if (automation_) {
    if (!use_json_interface_)
      AutomationMsg_WindowExecuteCommand::WriteReplyParams(reply_message_.get(),
                                                           true);
    new NavigationNotificationObserver(controller, automation_,
                                       reply_message_.release(),
                                       1, false, use_json_interface_);
  }
  delete this;
}
