void RenderViewImpl::focusedNodeChanged(const WebNode& node) {
  Send(new ViewHostMsg_FocusedNodeChanged(routing_id_, IsEditableNode(node)));

  FOR_EACH_OBSERVER(RenderViewObserver, observers_, FocusedNodeChanged(node));
}
