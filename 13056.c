void RenderWidgetHostImpl::SetBackgroundOpaque(bool opaque) {
  Send(new ViewMsg_SetBackgroundOpaque(GetRoutingID(), opaque));
}
