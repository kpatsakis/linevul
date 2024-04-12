void TestingAutomationProvider::GetInstantInfo(Browser* browser,
                                               DictionaryValue* args,
                                               IPC::Message* reply_message) {
  DictionaryValue* info = new DictionaryValue;
  if (browser->instant()) {
    InstantController* instant = browser->instant();
    info->SetBoolean("enabled", true);
    info->SetBoolean("active", (instant->GetPreviewContents() != NULL));
    info->SetBoolean("current", instant->IsCurrent());
    if (instant->GetPreviewContents() &&
        instant->GetPreviewContents()->web_contents()) {
      WebContents* contents = instant->GetPreviewContents()->web_contents();
      info->SetBoolean("loading", contents->IsLoading());
      info->SetString("location", contents->GetURL().spec());
      info->SetString("title", contents->GetTitle());
    }
  } else {
    info->SetBoolean("enabled", false);
  }
  scoped_ptr<DictionaryValue> return_value(new DictionaryValue);
  return_value->Set("instant", info);
  AutomationJSONReply(this, reply_message).SendSuccess(return_value.get());
}
