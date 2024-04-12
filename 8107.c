void WebContentsImpl::OnDialogClosed(int render_process_id,
                                     int render_frame_id,
                                     IPC::Message* reply_msg,
                                     bool dialog_was_suppressed,
                                     bool success,
                                     const base::string16& user_input) {
  RenderFrameHostImpl* rfh = RenderFrameHostImpl::FromID(render_process_id,
                                                         render_frame_id);
  last_dialog_suppressed_ = dialog_was_suppressed;

  if (is_showing_before_unload_dialog_ && !success) {
    if (rfh && rfh == rfh->frame_tree_node()->current_frame_host()) {
      rfh->frame_tree_node()->BeforeUnloadCanceled();
      controller_.DiscardNonCommittedEntries();
    }

    NotifyNavigationStateChanged(INVALIDATE_TYPE_URL);

    for (auto& observer : observers_)
      observer.BeforeUnloadDialogCancelled();
  }

  if (rfh) {
    rfh->JavaScriptDialogClosed(reply_msg, success, user_input);

    std::vector<protocol::PageHandler*> page_handlers =
        protocol::PageHandler::EnabledForWebContents(this);
    for (auto* handler : page_handlers)
      handler->DidCloseJavaScriptDialog(success, user_input);

  } else {
    delete reply_msg;
  }

  is_showing_javascript_dialog_ = false;
  is_showing_before_unload_dialog_ = false;
}
