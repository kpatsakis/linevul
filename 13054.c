void TestingAutomationProvider::GetViews(
    DictionaryValue* args, IPC::Message* reply_message) {
  ListValue* view_list = new ListValue();
  BrowserList::const_iterator browser_iter = BrowserList::begin();
  for (; browser_iter != BrowserList::end(); ++browser_iter) {
    Browser* browser = *browser_iter;
    for (int i = 0; i < browser->tab_count(); ++i) {
      DictionaryValue* dict = new DictionaryValue();
      AutomationId id = automation_util::GetIdForTab(
          browser->GetTabContentsWrapperAt(i));
      dict->Set("auto_id", id.ToValue());
      view_list->Append(dict);
    }
  }

  ExtensionProcessManager* extension_mgr =
      profile()->GetExtensionProcessManager();
  ExtensionProcessManager::const_iterator iter;
  for (iter = extension_mgr->begin(); iter != extension_mgr->end();
       ++iter) {
    ExtensionHost* host = *iter;
    AutomationId id = automation_util::GetIdForExtensionView(host);
    if (!id.is_valid())
      continue;
    DictionaryValue* dict = new DictionaryValue();
    dict->Set("auto_id", id.ToValue());
    dict->SetString("extension_id", host->extension_id());
    view_list->Append(dict);
  }
  DictionaryValue dict;
  dict.Set("views", view_list);
  AutomationJSONReply(this, reply_message).SendSuccess(&dict);
}
