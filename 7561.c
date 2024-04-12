void RenderWidgetHostImpl::AccessibilitySetFocus(int object_id) {
  Send(new AccessibilityMsg_SetFocus(GetRoutingID(), object_id));
}
