bool ShouldSendPinchGesture() {
  static bool pinch_allowed =
      CommandLine::ForCurrentProcess()->HasSwitch(switches::kEnableViewport) ||
      CommandLine::ForCurrentProcess()->HasSwitch(switches::kEnablePinch);
  return pinch_allowed;
}
