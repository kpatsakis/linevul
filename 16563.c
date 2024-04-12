bool ShouldSendPinchGesture() {
#if defined(OS_WIN)
  if (base::win::GetVersion() >= base::win::VERSION_WIN8)
    return true;
#endif
  static bool pinch_allowed =
      CommandLine::ForCurrentProcess()->HasSwitch(switches::kEnableViewport) ||
      CommandLine::ForCurrentProcess()->HasSwitch(switches::kEnablePinch);
  return pinch_allowed;
}
