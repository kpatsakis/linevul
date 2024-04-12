void RenderWidgetHostImpl::Focus() {
  Send(new ViewMsg_SetFocus(routing_id_, true));
}
