void TestingAutomationProvider::AutofillHighlightSuggestion(
    Browser* browser,
    DictionaryValue* args,
    IPC::Message* reply_message) {
  int tab_index;
  if (!args->GetInteger("tab_index", &tab_index)) {
    AutomationJSONReply(this, reply_message).SendError(
        "Invalid or missing args");
    return;
  }

  WebContents* web_contents = browser->GetWebContentsAt(tab_index);
  if (!web_contents) {
    AutomationJSONReply(this, reply_message).SendError(
        StringPrintf("No such tab at index %d", tab_index));
    return;
  }

  std::string direction;
  if (!args->GetString("direction", &direction) || (direction != "up" &&
                                                    direction != "down")) {
    AutomationJSONReply(this, reply_message).SendError(
        "Must specify a direction of either 'up' or 'down'.");
    return;
  }
  int key_code = (direction == "up") ? ui::VKEY_UP : ui::VKEY_DOWN;

  new AutofillDisplayedObserver(
      chrome::NOTIFICATION_AUTOFILL_DID_FILL_FORM_DATA,
      web_contents->GetRenderViewHost(), this, reply_message);
  SendWebKeyPressEventAsync(key_code, web_contents);
}
