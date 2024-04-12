MasterPreferences::MasterPreferences(const base::CommandLine& cmd_line)
    : distribution_(NULL),
      preferences_read_from_file_(false),
      chrome_(true),
      multi_install_(false) {
  InitializeFromCommandLine(cmd_line);
}
