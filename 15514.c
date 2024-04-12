void RenderWidgetHostImpl::SetInputMethodActive(bool activate) {
  Send(new ViewMsg_SetInputMethodActive(GetRoutingID(), activate));
}
