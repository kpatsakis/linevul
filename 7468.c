void AppLauncherHandler::HandleSaveAppPageName(const base::ListValue* args) {
  base::string16 name;
  CHECK(args->GetString(0, &name));

  double page_index;
  CHECK(args->GetDouble(1, &page_index));

  base::AutoReset<bool> auto_reset(&ignore_changes_, true);
  PrefService* prefs = Profile::FromWebUI(web_ui())->GetPrefs();
  ListPrefUpdate update(prefs, prefs::kNtpAppPageNames);
  base::ListValue* list = update.Get();
  list->Set(static_cast<size_t>(page_index), new base::StringValue(name));
}
