bool SendGetAppModalDialogMessageJSONRequest(
    AutomationMessageSender* sender,
    std::string* message,
    std::string* error_msg) {
  DictionaryValue dict;
  dict.SetString("command", "GetAppModalDialogMessage");
  DictionaryValue reply_dict;
  if (!SendAutomationJSONRequest(sender, dict, &reply_dict, error_msg))
    return false;
  return reply_dict.GetString("message", message);
}
