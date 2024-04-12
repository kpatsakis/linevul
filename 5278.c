void Browser::RegisterAppPrefs(const std::string& app_name) {
  static std::set<std::string>* g_app_names = NULL;

  if (!g_app_names)
    g_app_names = new std::set<std::string>;

  if (g_app_names->find(app_name) != g_app_names->end())
    return;
  g_app_names->insert(app_name);

  std::string window_pref(prefs::kBrowserWindowPlacement);
  window_pref.append("_");
  window_pref.append(app_name);
  PrefService* prefs = g_browser_process->local_state();
  DCHECK(prefs);

  prefs->RegisterDictionaryPref(window_pref.c_str());
}
