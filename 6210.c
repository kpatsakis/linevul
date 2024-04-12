bool SendMouseDragJSONRequest(
    AutomationMessageSender* sender,
    int browser_index,
    int tab_index,
    int start_x,
    int start_y,
    int end_x,
    int end_y,
    std::string* error_msg) {
  DictionaryValue dict;
  dict.SetString("command", "WebkitMouseDrag");
  dict.SetInteger("windex", browser_index);
  dict.SetInteger("tab_index", tab_index);
  dict.SetInteger("start_x", start_x);
  dict.SetInteger("start_y", start_y);
  dict.SetInteger("end_x", end_x);
  dict.SetInteger("end_y", end_y);
  DictionaryValue reply_dict;
  return SendAutomationJSONRequest(sender, dict, &reply_dict, error_msg);
}
