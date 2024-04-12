bool SendGoBackJSONRequest(
    AutomationMessageSender* sender,
    int browser_index,
    int tab_index,
    std::string* error_msg) {
  DictionaryValue dict;
  dict.SetString("command", "GoBack");
  dict.SetInteger("windex", browser_index);
  dict.SetInteger("tab_index", tab_index);
  DictionaryValue reply_dict;
  return SendAutomationJSONRequest(sender, dict, &reply_dict, error_msg);
}
