void ShellMainDelegate::ZygoteForked() {
  if (base::CommandLine::ForCurrentProcess()->HasSwitch(
          switches::kEnableCrashReporter)) {
    std::string process_type =
        base::CommandLine::ForCurrentProcess()->GetSwitchValueASCII(
            switches::kProcessType);
    breakpad::InitCrashReporter(process_type);
  }
}
