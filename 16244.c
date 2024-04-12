void RenderWidgetHostImpl::ForwardMouseEvent(const WebMouseEvent& mouse_event) {
  if (GetView()->IsInVR() &&
      (is_in_gesture_scroll_[blink::kWebGestureDeviceTouchpad] ||
       is_in_touchpad_gesture_fling_)) {
    return;
  }

  ForwardMouseEventWithLatencyInfo(mouse_event,
                                   ui::LatencyInfo(ui::SourceEventType::MOUSE));
  if (owner_delegate_)
    owner_delegate_->RenderWidgetDidForwardMouseEvent(mouse_event);
}
