std::unique_ptr<WebRunnerNetLog> CreateNetLog() {
  std::unique_ptr<WebRunnerNetLog> result;

  const base::CommandLine* command_line =
      base::CommandLine::ForCurrentProcess();
  if (command_line->HasSwitch(network::switches::kLogNetLog)) {
    base::FilePath log_path =
        command_line->GetSwitchValuePath(network::switches::kLogNetLog);
    result = std::make_unique<WebRunnerNetLog>(log_path);
  }

  return result;
}
