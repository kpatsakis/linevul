void RenderWidgetHostViewAura::GestureEventAck(int gesture_event_type,
                                               InputEventAckState ack_result) {
  if (touch_editing_client_)
    touch_editing_client_->GestureEventAck(gesture_event_type);
}
