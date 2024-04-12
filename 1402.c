void SimulateTapWithModifiersAt(WebContents* web_contents,
                                unsigned modifiers,
                                const gfx::Point& point) {
  blink::WebGestureEvent tap(blink::WebGestureEvent::kGestureTap, modifiers,
                             ui::EventTimeForNow(),
                             blink::kWebGestureDeviceTouchpad);
  tap.SetPositionInWidget(gfx::PointF(point));
  RenderWidgetHostImpl* widget_host = RenderWidgetHostImpl::From(
      web_contents->GetRenderViewHost()->GetWidget());
  widget_host->ForwardGestureEvent(tap);
}
