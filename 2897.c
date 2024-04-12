  void SendScrollBeginAckIfNeeded(InputEventAckState ack_result) {
    MockWidgetInputHandler::MessageVector events =
        GetAndResetDispatchedMessages();
    SendScrollBeginAckIfNeeded(events, ack_result);
  }
