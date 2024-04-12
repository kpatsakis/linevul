bool ResourceMessageFilter::CheckBenchmarkingEnabled() {
  static bool checked = false;
  static bool result = false;
  if (!checked) {
    const CommandLine& command_line = *CommandLine::ForCurrentProcess();
    result = command_line.HasSwitch(switches::kEnableBenchmarking);
    checked = true;
  }
  return result;
}
