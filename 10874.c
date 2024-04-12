void TestingAutomationProvider::FindInPage(
    Browser* browser,
    DictionaryValue* args,
    IPC::Message* reply_message) {
  std::string error_message;
  TabContentsWrapper* tab_contents =
      GetTabContentsWrapperFromDict(browser, args, &error_message);
  if (!tab_contents) {
    AutomationJSONReply(this, reply_message).SendError(error_message);
    return;
  }
  string16 search_string;
  bool forward;
  bool match_case;
  bool find_next;
  if (!args->GetString("search_string", &search_string)) {
    AutomationJSONReply(this, reply_message).
        SendError("Must include search_string string.");
    return;
  }
  if (!args->GetBoolean("forward", &forward)) {
    AutomationJSONReply(this, reply_message).
        SendError("Must include forward boolean.");
    return;
  }
  if (!args->GetBoolean("match_case", &match_case)) {
    AutomationJSONReply(this, reply_message).
        SendError("Must include match_case boolean.");
    return;
  }
  if (!args->GetBoolean("find_next", &find_next)) {
    AutomationJSONReply(this, reply_message).
        SendError("Must include find_next boolean.");
    return;
  }
  SendFindRequest(tab_contents->web_contents(),
                  true,
                  search_string,
                  forward,
                  match_case,
                  find_next,
                  reply_message);
}
