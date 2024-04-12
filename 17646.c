void MigrateBrowserPrefs(PrefService* user_prefs, PrefService* local_state) {
  int current_version =
      local_state->GetInteger(prefs::kMultipleProfilePrefMigration);

  if ((current_version & WINDOWS_PREFS) == 0) {
    local_state->RegisterIntegerPref(prefs::kDevToolsSplitLocation, -1);
    if (local_state->HasPrefPath(prefs::kDevToolsSplitLocation)) {
      user_prefs->SetInteger(prefs::kDevToolsSplitLocation,
          local_state->GetInteger(prefs::kDevToolsSplitLocation));
    }
    local_state->ClearPref(prefs::kDevToolsSplitLocation);

    local_state->RegisterDictionaryPref(prefs::kBrowserWindowPlacement);
    if (local_state->HasPrefPath(prefs::kBrowserWindowPlacement)) {
      const PrefService::Preference* pref =
          local_state->FindPreference(prefs::kBrowserWindowPlacement);
      DCHECK(pref);
      user_prefs->Set(prefs::kBrowserWindowPlacement, *(pref->GetValue()));
    }
    local_state->ClearPref(prefs::kBrowserWindowPlacement);

    local_state->SetInteger(prefs::kMultipleProfilePrefMigration,
                            current_version | WINDOWS_PREFS);
  }
}
