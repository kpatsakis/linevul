void RenderWidgetHostImpl::ForwardGestureEventImmediately(
    const WebKit::WebGestureEvent& gesture_event) {
  if (ignore_input_events_ || process_->IgnoreInputEvents())
    return;
  ForwardInputEvent(gesture_event, sizeof(WebGestureEvent), false);
}
