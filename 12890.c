void TestingAutomationProvider::WaitForNotificationCount(
    Browser* browser,
    DictionaryValue* args,
    IPC::Message* reply_message) {
  int count;
  if (!args->GetInteger("count", &count)) {
    AutomationJSONReply(this, reply_message)
        .SendError("'count' missing or invalid.");
    return;
  }
  new OnNotificationBalloonCountObserver(this, reply_message, count);
}
