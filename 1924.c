void RenderViewImpl::numberOfWheelEventHandlersChanged(unsigned num_handlers) {
  Send(new ViewHostMsg_DidChangeNumWheelEvents(routing_id_, num_handlers));
}
