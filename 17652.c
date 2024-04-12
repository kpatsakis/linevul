bool IsInputViewEnabled() {
  if (base::CommandLine::ForCurrentProcess()->HasSwitch(
          switches::kEnableInputView))
    return true;
  if (base::CommandLine::ForCurrentProcess()->HasSwitch(
          switches::kDisableInputView))
    return false;
  return true;
}
