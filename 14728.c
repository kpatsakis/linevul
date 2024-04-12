bool IsNetworkSettingsConfigEnabled() {
  return !base::CommandLine::ForCurrentProcess()->HasSwitch(
      chromeos::switches::kDisableNetworkSettingsConfig);
}
