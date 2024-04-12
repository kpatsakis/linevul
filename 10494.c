void TestingAutomationProvider::LockScreen(DictionaryValue* args,
                                           IPC::Message* reply_message) {
  new ScreenLockUnlockObserver(this, reply_message, true);
  DBusThreadManager::Get()->GetPowerManagerClient()->
      NotifyScreenLockRequested();
}
