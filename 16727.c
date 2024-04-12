void ChromeContentBrowserClient::RegisterUserPrefs(
    PrefRegistrySyncable* registry) {
  registry->RegisterBooleanPref(prefs::kDisable3DAPIs,
                                false,
                                PrefRegistrySyncable::UNSYNCABLE_PREF);
  registry->RegisterBooleanPref(prefs::kEnableHyperlinkAuditing,
                                true,
                                PrefRegistrySyncable::UNSYNCABLE_PREF);
  registry->RegisterBooleanPref(prefs::kEnableMemoryInfo,
                                false,
                                PrefRegistrySyncable::UNSYNCABLE_PREF);
}
