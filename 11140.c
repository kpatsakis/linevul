void BrowserRenderProcessHost::OnMessageReceived(const IPC::Message& msg) {
  mark_child_process_activity_time();
  if (msg.routing_id() == MSG_ROUTING_CONTROL) {
    bool msg_is_ok = true;
    IPC_BEGIN_MESSAGE_MAP_EX(BrowserRenderProcessHost, msg, msg_is_ok)
      IPC_MESSAGE_HANDLER(ViewHostMsg_PageContents, OnPageContents)
      IPC_MESSAGE_HANDLER(ViewHostMsg_UpdatedCacheStats,
                          OnUpdatedCacheStats)
      IPC_MESSAGE_HANDLER(ViewHostMsg_SuddenTerminationChanged,
                          SuddenTerminationChanged);
      IPC_MESSAGE_HANDLER(ViewHostMsg_ExtensionAddListener,
                          OnExtensionAddListener)
      IPC_MESSAGE_HANDLER(ViewHostMsg_ExtensionRemoveListener,
                          OnExtensionRemoveListener)
      IPC_MESSAGE_HANDLER(ViewHostMsg_ExtensionCloseChannel,
                          OnExtensionCloseChannel)
      IPC_MESSAGE_UNHANDLED_ERROR()
    IPC_END_MESSAGE_MAP_EX()

    if (!msg_is_ok) {
      ReceivedBadMessage(msg.type());
    }
    return;
  }

  IPC::Channel::Listener* listener = GetListenerByID(msg.routing_id());
  if (!listener) {
    if (msg.is_sync()) {
      IPC::Message* reply = IPC::SyncMessage::GenerateReply(&msg);
      reply->set_reply_error();
      Send(reply);
    }
    return;
  }
  listener->OnMessageReceived(msg);
}
