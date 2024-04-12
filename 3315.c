bool RenderWidgetHostViewAura::NeedsMouseCapture() {
#if defined(OS_LINUX) && !defined(OS_CHROMEOS)
  return NeedsInputGrab();
#endif
  return false;
}
