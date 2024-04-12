bool SendNativeKeyEventJSONRequest(
    AutomationMessageSender* sender,
    int browser_index,
    int tab_index,
    ui::KeyboardCode key_code,
    int modifiers,
    std::string* error_msg) {
  DictionaryValue dict;
  dict.SetString("command", "SendOSLevelKeyEventToTab");
  dict.SetInteger("windex", browser_index);
  dict.SetInteger("tab_index", tab_index);
  dict.SetInteger("keyCode", key_code);
  dict.SetInteger("modifiers", modifiers);
  DictionaryValue reply_dict;
  return SendAutomationJSONRequest(sender, dict, &reply_dict, error_msg);
}
