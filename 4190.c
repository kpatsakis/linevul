bool ListenToGuestWebContents(
    AccessibilityNotificationWaiter* accessibility_waiter,
    WebContents* web_contents) {
  accessibility_waiter->ListenToAdditionalFrame(
      static_cast<RenderFrameHostImpl*>(web_contents->GetMainFrame()));
  return true;
}
