void WebContentsImpl::AddAccessibilityMode(AccessibilityMode mode) {
  SetAccessibilityMode(AddAccessibilityModeTo(accessibility_mode_, mode));
}
