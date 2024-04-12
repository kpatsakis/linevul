void TestingAutomationProvider::GetOmniboxInfo(Browser* browser,
                                               DictionaryValue* args,
                                               IPC::Message* reply_message) {
  scoped_ptr<DictionaryValue> return_value(new DictionaryValue);

  LocationBar* loc_bar = browser->window()->GetLocationBar();
  OmniboxView* omnibox_view = loc_bar->location_entry();
  AutocompleteEditModel* model = omnibox_view->model();

  ListValue* matches = new ListValue;
  const AutocompleteResult& result = model->result();
  for (AutocompleteResult::const_iterator i = result.begin();
       i != result.end(); ++i) {
    const AutocompleteMatch& match = *i;
    DictionaryValue* item = new DictionaryValue;  // owned by return_value
    item->SetString("type", AutocompleteMatch::TypeToString(match.type));
    item->SetBoolean("starred", match.starred);
    item->SetString("destination_url", match.destination_url.spec());
    item->SetString("contents", match.contents);
    item->SetString("description", match.description);
    matches->Append(item);
  }
  return_value->Set("matches", matches);

  DictionaryValue* properties = new DictionaryValue;  // owned by return_value
  properties->SetBoolean("has_focus", model->has_focus());
  properties->SetBoolean("query_in_progress",
                         !model->autocomplete_controller()->done());
  properties->SetString("keyword", model->keyword());
  properties->SetString("text", omnibox_view->GetText());
  return_value->Set("properties", properties);

  AutomationJSONReply(this, reply_message).SendSuccess(return_value.get());
}
