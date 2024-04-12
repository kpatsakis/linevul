void RenderViewTest::SendWebMouseEvent(
    const blink::WebMouseEvent& mouse_event) {
  RenderViewImpl* impl = static_cast<RenderViewImpl*>(view_);
  impl->OnMessageReceived(
      InputMsg_HandleInputEvent(0, &mouse_event, ui::LatencyInfo(), false));
}
