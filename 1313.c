void RenderWidgetHostImpl::OnAutoscrollFling(const gfx::Vector2dF& velocity) {
  WebGestureEvent event = SyntheticWebGestureEventBuilder::Build(
      WebInputEvent::kGestureFlingStart,
      blink::kWebGestureDeviceSyntheticAutoscroll);
  event.data.fling_start.velocity_x = velocity.x();
  event.data.fling_start.velocity_y = velocity.y();

  ForwardGestureEventWithLatencyInfo(
      event, ui::LatencyInfo(ui::SourceEventType::OTHER));
}
