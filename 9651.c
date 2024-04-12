bool StartupBrowserCreator::ProcessLastOpenedProfiles(
    const base::CommandLine& command_line,
    const base::FilePath& cur_dir,
    chrome::startup::IsProcessStartup is_process_startup,
    chrome::startup::IsFirstRun is_first_run,
    Profile* last_used_profile,
    const Profiles& last_opened_profiles) {
  base::CommandLine command_line_without_urls(command_line.GetProgram());
  for (auto& switch_pair : command_line.GetSwitches()) {
    command_line_without_urls.AppendSwitchNative(switch_pair.first,
                                                 switch_pair.second);
  }

  size_t DEBUG_num_profiles_on_entry = last_opened_profiles.size();
  base::debug::Alias(&DEBUG_num_profiles_on_entry);
  int DEBUG_loop_counter = 0;
  base::debug::Alias(&DEBUG_loop_counter);

  base::debug::Alias(&last_opened_profiles);
  const Profile* DEBUG_profile_0 = nullptr;
  const Profile* DEBUG_profile_1 = nullptr;
  if (!last_opened_profiles.empty())
    DEBUG_profile_0 = last_opened_profiles[0];
  if (last_opened_profiles.size() > 1)
    DEBUG_profile_1 = last_opened_profiles[1];
  base::debug::Alias(&DEBUG_profile_0);
  base::debug::Alias(&DEBUG_profile_1);

  size_t DEBUG_num_profiles_at_loop_start = std::numeric_limits<size_t>::max();
  base::debug::Alias(&DEBUG_num_profiles_at_loop_start);

  auto DEBUG_it_begin = last_opened_profiles.begin();
  base::debug::Alias(&DEBUG_it_begin);
  auto DEBUG_it_end = last_opened_profiles.end();
  base::debug::Alias(&DEBUG_it_end);

  for (auto it = last_opened_profiles.begin(); it != last_opened_profiles.end();
       ++it, ++DEBUG_loop_counter) {
    DEBUG_num_profiles_at_loop_start = last_opened_profiles.size();
    DCHECK(!(*it)->IsGuestSession());

#if !defined(OS_CHROMEOS)
    if (!CanOpenProfileOnStartup(*it))
      continue;

    if (last_used_profile->IsGuestSession())
      last_used_profile = *it;
#endif

    SessionStartupPref startup_pref = GetSessionStartupPref(command_line, *it);
    if (*it != last_used_profile &&
        startup_pref.type == SessionStartupPref::DEFAULT &&
        !HasPendingUncleanExit(*it)) {
      continue;
    }
    if (!LaunchBrowser((*it == last_used_profile) ? command_line
                                                  : command_line_without_urls,
                       *it, cur_dir, is_process_startup, is_first_run)) {
      return false;
    }
    is_process_startup = chrome::startup::IS_NOT_PROCESS_STARTUP;
  }

#if !defined(OS_CHROMEOS)
  if (is_process_startup == chrome::startup::IS_PROCESS_STARTUP)
    ShowUserManagerOnStartup(command_line);
  else
#endif
    profile_launch_observer.Get().set_profile_to_activate(last_used_profile);
  return true;
}
