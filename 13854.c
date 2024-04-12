void BrowserActionsContainer::RegisterUserPrefs(PrefService* prefs) {
  prefs->RegisterIntegerPref(prefs::kBrowserActionContainerWidth, 0);
}
