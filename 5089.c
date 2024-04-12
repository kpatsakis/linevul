bool BrowserInit::LaunchWithProfile::OpenStartupURLs(
    bool is_process_startup,
    const std::vector<GURL>& urls_to_open) {
  SessionStartupPref pref = GetSessionStartupPref(command_line_, profile_);
  if (is_process_startup &&
      command_line_.HasSwitch(switches::kTestingChannelID) &&
      !command_line_.HasSwitch(switches::kRestoreLastSession) &&
      browser_defaults::kDefaultSessionStartupType !=
      SessionStartupPref::DEFAULT) {
    return false;
  }
  switch (pref.type) {
    case SessionStartupPref::LAST:
      if (!is_process_startup)
        return false;

      if (!profile_->DidLastSessionExitCleanly() &&
          !command_line_.HasSwitch(switches::kRestoreLastSession)) {
        return false;
      }
      SessionRestore::RestoreSessionSynchronously(profile_, urls_to_open);
      return true;

    case SessionStartupPref::URLS:
      if (urls_to_open.empty()) {
        if (pref.urls.empty()) {
          std::vector<GURL> urls;
          urls.push_back(GURL(chrome::kChromeUINewTabURL));
          OpenURLsInBrowser(NULL, is_process_startup, urls);
          return true;
        }
        OpenURLsInBrowser(NULL, is_process_startup, pref.urls);
        return true;
      }
      return false;

    default:
      return false;
  }
}
