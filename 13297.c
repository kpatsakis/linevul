TabAppendedNotificationObserver::TabAppendedNotificationObserver(
    Browser* parent,
    AutomationProvider* automation,
    IPC::Message* reply_message,
    bool use_json_interface)
    : TabStripNotificationObserver(chrome::NOTIFICATION_TAB_PARENTED,
                                   automation),
      parent_(parent),
      reply_message_(reply_message),
      use_json_interface_(use_json_interface) {
}
