DragTargetDropAckNotificationObserver::DragTargetDropAckNotificationObserver(
    AutomationProvider* automation,
    IPC::Message* reply_message)
    : automation_(automation->AsWeakPtr()),
      reply_message_(reply_message) {
  registrar_.Add(
      this,
      content::NOTIFICATION_RENDER_VIEW_HOST_DID_RECEIVE_DRAG_TARGET_DROP_ACK,
      content::NotificationService::AllSources());
  registrar_.Add(
      this,
      chrome::NOTIFICATION_APP_MODAL_DIALOG_SHOWN,
      content::NotificationService::AllSources());
}
