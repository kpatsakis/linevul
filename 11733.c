void CapturerMac::DisplaysReconfiguredCallback(
    CGDirectDisplayID display,
    CGDisplayChangeSummaryFlags flags,
    void *user_parameter) {
  if (display == CGMainDisplayID()) {
    CapturerMac *capturer = reinterpret_cast<CapturerMac *>(user_parameter);
    if (flags & kCGDisplayBeginConfigurationFlag) {
      capturer->EnableCapture(false);
    } else {
      capturer->EnableCapture(true);
      capturer->ScreenConfigurationChanged();
    }
  }
}
