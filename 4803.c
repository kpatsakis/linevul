void TestingAutomationProvider::WaitForBrowserWindowCountToBecome(
    int target_count,
    IPC::Message* reply_message) {
  if (static_cast<int>(BrowserList::size()) == target_count) {
    AutomationMsg_WaitForBrowserWindowCountToBecome::WriteReplyParams(
        reply_message, true);
    Send(reply_message);
    return;
  }

  new BrowserCountChangeNotificationObserver(target_count, this, reply_message);
}
