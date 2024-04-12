void RenderFrameHostImpl::JavaScriptDialogClosed(
    IPC::Message* reply_msg,
    bool success,
    const base::string16& user_input,
    bool dialog_was_suppressed) {
  GetProcess()->SetIgnoreInputEvents(false);

  SendJavaScriptDialogReply(reply_msg, success, user_input);

  for (RenderFrameHostImpl* frame = this; frame; frame = frame->GetParent()) {
    if (frame->is_waiting_for_beforeunload_ack_) {
      if (dialog_was_suppressed) {
        frame->SimulateBeforeUnloadAck();
      } else if (frame->beforeunload_timeout_) {
        frame->beforeunload_timeout_->Start(
            TimeDelta::FromMilliseconds(RenderViewHostImpl::kUnloadTimeoutMS));
      }
    }
  }
}
