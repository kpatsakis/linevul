void RenderFrameImpl::SendUpdateState() {
  if (current_history_item_.IsNull())
    return;

  Send(new FrameHostMsg_UpdateState(
      routing_id_, SingleHistoryItemToPageState(current_history_item_)));
}
