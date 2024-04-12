void RenderWidgetHostImpl::ForwardGestureEventWithLatencyInfo(
    const blink::WebGestureEvent& gesture_event,
    const ui::LatencyInfo& ui_latency) {
  TRACE_EVENT0("input", "RenderWidgetHostImpl::ForwardGestureEvent");
  if (ShouldDropInputEvents())
    return;

  if (gesture_event.type == blink::WebInputEvent::GestureScrollBegin) {
    DCHECK(!is_in_gesture_scroll_);
    is_in_gesture_scroll_ = true;
  } else if (gesture_event.type == blink::WebInputEvent::GestureScrollEnd ||
             gesture_event.type == blink::WebInputEvent::GestureFlingStart) {
    DCHECK(is_in_gesture_scroll_ ||
           (gesture_event.type == blink::WebInputEvent::GestureFlingStart &&
            gesture_event.sourceDevice ==
                blink::WebGestureDevice::WebGestureDeviceTouchpad));
    is_in_gesture_scroll_ = false;
  }

  bool scroll_update_needs_wrapping =
      gesture_event.type == blink::WebInputEvent::GestureScrollUpdate &&
      gesture_event.resendingPluginId != -1 && !is_in_gesture_scroll_;

  if (scroll_update_needs_wrapping) {
    ForwardGestureEventWithLatencyInfo(
        CreateScrollBeginForWrapping(gesture_event), ui::LatencyInfo());
  }

  if (delegate_->PreHandleGestureEvent(gesture_event))
    return;

  GestureEventWithLatencyInfo gesture_with_latency(gesture_event, ui_latency);
  latency_tracker_.OnInputEvent(gesture_event, &gesture_with_latency.latency);
  input_router_->SendGestureEvent(gesture_with_latency);

  if (scroll_update_needs_wrapping) {
    ForwardGestureEventWithLatencyInfo(
        CreateScrollEndForWrapping(gesture_event), ui::LatencyInfo());
  }
}
