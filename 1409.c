void TestingAutomationProvider::SignoutInScreenLocker(
    DictionaryValue* args, IPC::Message* reply_message) {
  AutomationJSONReply reply(this, reply_message);
  chromeos::ScreenLocker* screen_locker =
      chromeos::ScreenLocker::default_screen_locker();
  if (!screen_locker) {
    reply.SendError(
        "No default screen locker. Are you sure the screen is locked?");
    return;
  }

  reply.SendSuccess(NULL);
  screen_locker->Signout();
}
