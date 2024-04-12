void RenderFrameImpl::DidHandleOnloadEvents() {
  if (!frame_->Parent()) {
    Send(new FrameHostMsg_DocumentOnLoadCompleted(routing_id_));
  }
  for (auto& observer : observers_)
    observer.DidHandleOnloadEvents();
}
