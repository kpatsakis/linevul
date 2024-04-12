void HostNPScriptObject::NotifyAccessCode(bool success) {
  DCHECK_EQ(MessageLoop::current(), host_context_.main_message_loop());
  if (state_ == kRequestedAccessCode) {
    SetState(success ? kReceivedAccessCode : kError);
  }
}
