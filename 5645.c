bool IsGuestModeEnforced(const base::CommandLine& command_line,
                         bool show_warning) {
#if defined(OS_LINUX) || defined(OS_WIN) || defined(OS_MACOSX)
  PrefService* service = g_browser_process->local_state();
  DCHECK(service);

  if (command_line.HasSwitch(switches::kGuest) ||
      service->GetBoolean(prefs::kBrowserGuestModeEnforced)) {
    if (service->GetBoolean(prefs::kBrowserGuestModeEnabled))
      return true;
    if (show_warning) {
      LOG(WARNING) << "Guest mode disabled by policy, launching a normal "
                   << "browser session.";
    }
  }
#endif
  return false;
}
