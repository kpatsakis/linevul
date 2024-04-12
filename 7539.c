void BrowserEventRouter::TabClosingAt(TabStripModel* tab_strip_model,
                                      WebContents* contents,
                                      int index) {
  int tab_id = ExtensionTabUtil::GetTabId(contents);

  scoped_ptr<ListValue> args(new ListValue());
  args->Append(Value::CreateIntegerValue(tab_id));

  DictionaryValue* object_args = new DictionaryValue();
  object_args->SetBoolean(tab_keys::kWindowClosing,
                          tab_strip_model->closing_all());
  args->Append(object_args);

  Profile* profile = Profile::FromBrowserContext(contents->GetBrowserContext());
  DispatchEvent(profile, events::kOnTabRemoved, args.Pass(),
                EventRouter::USER_GESTURE_UNKNOWN);

  int removed_count = tab_entries_.erase(tab_id);
  DCHECK_GT(removed_count, 0);

  UnregisterForTabNotifications(contents);
}
