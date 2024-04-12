bool SettingsWindowEnabled() {
#if defined(OS_CHROMEOS)
  return !base::CommandLine::ForCurrentProcess()->HasSwitch(
      ::switches::kDisableSettingsWindow);
#else
  return base::CommandLine::ForCurrentProcess()->HasSwitch(
      ::switches::kEnableSettingsWindow);
#endif
}
