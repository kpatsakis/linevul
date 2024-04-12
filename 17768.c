void RenderWidgetHostViewAura::OnScrollEvent(ui::ScrollEvent* event) {
  TRACE_EVENT0("input", "RenderWidgetHostViewAura::OnScrollEvent");
  if (touch_editing_client_ && touch_editing_client_->HandleInputEvent(event))
    return;

  if (event->type() == ui::ET_SCROLL) {
#if !defined(OS_WIN)
    if (event->finger_count() != 2)
      return;
#endif
    blink::WebGestureEvent gesture_event =
        MakeWebGestureEventFlingCancel();
    host_->ForwardGestureEvent(gesture_event);
    blink::WebMouseWheelEvent mouse_wheel_event =
        MakeWebMouseWheelEvent(event);
    host_->ForwardWheelEvent(mouse_wheel_event);
    RecordAction(base::UserMetricsAction("TrackpadScroll"));
  } else if (event->type() == ui::ET_SCROLL_FLING_START ||
             event->type() == ui::ET_SCROLL_FLING_CANCEL) {
    blink::WebGestureEvent gesture_event =
        MakeWebGestureEvent(event);
    host_->ForwardGestureEvent(gesture_event);
    if (event->type() == ui::ET_SCROLL_FLING_START)
      RecordAction(base::UserMetricsAction("TrackpadScrollFling"));
  }

  event->SetHandled();
}
