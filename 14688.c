void RenderFrameHostImpl::OnRunJavaScriptDialog(
    const base::string16& message,
    const base::string16& default_prompt,
    const GURL& frame_url,
    JavaScriptDialogType dialog_type,
    IPC::Message* reply_msg) {
  if (dialog_type == JavaScriptDialogType::JAVASCRIPT_DIALOG_TYPE_ALERT)
    GetFrameResourceCoordinator()->OnAlertFired();

  if (IsWaitingForUnloadACK()) {
    SendJavaScriptDialogReply(reply_msg, true, base::string16());
    return;
  }

  int32_t message_length = static_cast<int32_t>(message.length());
  if (GetParent()) {
    UMA_HISTOGRAM_COUNTS("JSDialogs.CharacterCount.Subframe", message_length);
  } else {
    UMA_HISTOGRAM_COUNTS("JSDialogs.CharacterCount.MainFrame", message_length);
  }

  GetProcess()->SetIgnoreInputEvents(true);
  delegate_->RunJavaScriptDialog(this, message, default_prompt, frame_url,
                                 dialog_type, reply_msg);
}
