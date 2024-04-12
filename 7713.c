bool SendGetCookiesJSONRequest(
    AutomationMessageSender* sender,
    const std::string& url,
    ListValue** cookies,
    std::string* error_msg) {
  DictionaryValue dict;
  dict.SetString("command", "GetCookies");
  dict.SetString("url", url);
  DictionaryValue reply_dict;
  if (!SendAutomationJSONRequest(sender, dict, &reply_dict, error_msg))
    return false;
  Value* cookies_unscoped_value;
  if (!reply_dict.Remove("cookies", &cookies_unscoped_value))
    return false;
  scoped_ptr<Value> cookies_value(cookies_unscoped_value);
  if (!cookies_value->IsType(Value::TYPE_LIST))
    return false;
  *cookies = static_cast<ListValue*>(cookies_value.release());
  return true;
}
