void ProfileSyncService::InitSettings() {
  const CommandLine& command_line = *CommandLine::ForCurrentProcess();

  if (command_line.HasSwitch(switches::kSyncServiceURL)) {
    std::string value(command_line.GetSwitchValueASCII(
        switches::kSyncServiceURL));
    if (!value.empty()) {
      GURL custom_sync_url(value);
      if (custom_sync_url.is_valid()) {
        sync_service_url_ = custom_sync_url;
      } else {
        LOG(WARNING) << "The following sync URL specified at the command-line "
                     << "is invalid: " << value;
      }
    }
  }
}
