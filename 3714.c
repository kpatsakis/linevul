void TestingAutomationProvider::AutofillAcceptSelection(
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

  new AutofillDisplayedObserver(
      chrome::NOTIFICATION_AUTOFILL_DID_FILL_FORM_DATA,
      web_contents->GetRenderViewHost(), this, reply_message);
  SendWebKeyPressEventAsync(ui::VKEY_RETURN, web_contents);
}
