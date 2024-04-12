void RenderViewImpl::postAccessibilityNotification(
    const WebAccessibilityObject& obj,
    WebAccessibilityNotification notification) {
  renderer_accessibility_->PostAccessibilityNotification(obj, notification);
}
