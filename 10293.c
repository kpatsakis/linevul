void RenderWidgetHostImpl::ForwardWheelEventWithLatencyInfo(
    const blink::WebMouseWheelEvent& wheel_event,
    const ui::LatencyInfo& latency) {
  TRACE_EVENT2("input", "RenderWidgetHostImpl::ForwardWheelEvent", "dx",
               wheel_event.delta_x, "dy", wheel_event.delta_y);

  if (ShouldDropInputEvents())
    return;

  auto* touch_emulator = GetExistingTouchEmulator();
  if (touch_emulator && touch_emulator->HandleMouseWheelEvent(wheel_event))
    return;

  MouseWheelEventWithLatencyInfo wheel_with_latency(wheel_event, latency);
  DispatchInputEventWithLatencyInfo(wheel_event, &wheel_with_latency.latency);
  input_router_->SendWheelEvent(wheel_with_latency);
}
