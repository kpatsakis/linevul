void WebContentsImpl::SetHistoryOffsetAndLength(int history_offset,
                                                int history_length) {
  SendPageMessage(new PageMsg_SetHistoryOffsetAndLength(
      MSG_ROUTING_NONE, history_offset, history_length));
}
