void WebContentsImpl::EnableTreeOnlyAccessibilityMode() {
  if (GetAccessibilityMode() != AccessibilityModeOff) {
    for (RenderFrameHost* rfh : GetAllFrames())
      ResetAccessibility(rfh);
  } else {
    AddAccessibilityMode(AccessibilityModeTreeOnly);
  }
}
