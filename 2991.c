JsArgList SyncManager::SyncInternal::GetNotificationState(
    const JsArgList& args) {
  bool notifications_enabled = allstatus_.status().notifications_enabled;
  ListValue return_args;
  return_args.Append(Value::CreateBooleanValue(notifications_enabled));
  return JsArgList(&return_args);
}
