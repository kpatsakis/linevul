void SendRoutedGestureTapSequence(content::WebContents* web_contents,
                                  gfx::Point point) {
  RenderWidgetHostViewAura* rwhva = static_cast<RenderWidgetHostViewAura*>(
      web_contents->GetRenderWidgetHostView());
  ui::GestureEventDetails gesture_tap_down_details(ui::ET_GESTURE_TAP_DOWN);
  gesture_tap_down_details.set_device_type(
      ui::GestureDeviceType::DEVICE_TOUCHSCREEN);
  ui::GestureEvent gesture_tap_down(point.x(), point.y(), 0,
                                    base::TimeTicks::Now(),
                                    gesture_tap_down_details);
  rwhva->OnGestureEvent(&gesture_tap_down);
  ui::GestureEventDetails gesture_tap_details(ui::ET_GESTURE_TAP);
  gesture_tap_details.set_device_type(
      ui::GestureDeviceType::DEVICE_TOUCHSCREEN);
  gesture_tap_details.set_tap_count(1);
  ui::GestureEvent gesture_tap(point.x(), point.y(), 0, base::TimeTicks::Now(),
                               gesture_tap_details);
  rwhva->OnGestureEvent(&gesture_tap);
}
