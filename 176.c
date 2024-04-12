bool PowerOverlayEnabled() {
  return base::CommandLine::ForCurrentProcess()->HasSwitch(
      ::switches::kEnablePowerOverlay);
}
