BrowserInit::LaunchWithProfile::LaunchWithProfile(
    const FilePath& cur_dir,
    const CommandLine& command_line,
    BrowserInit* browser_init,
    IsFirstRun is_first_run)
        : cur_dir_(cur_dir),
          command_line_(command_line),
          profile_(NULL),
          browser_init_(browser_init),
          is_first_run_(is_first_run == IS_FIRST_RUN) {
}
