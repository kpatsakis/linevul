bool RenderMessageFilter::CheckPreparsedJsCachingEnabled() const {
  static bool checked = false;
  static bool result = false;
  if (!checked) {
    const CommandLine& command_line = *CommandLine::ForCurrentProcess();
    result = command_line.HasSwitch(switches::kEnablePreparsedJsCaching);
    checked = true;
  }
  return result;
}