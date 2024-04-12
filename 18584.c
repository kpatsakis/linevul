void RenderWidgetHostImpl::SetActive(bool active) {
  Send(new ViewMsg_SetActive(routing_id_, active));
}
