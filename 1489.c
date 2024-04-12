  void HandleMousePressEvent(int x, int y) {
    WebMouseEvent event(
        WebInputEvent::kMouseDown, WebFloatPoint(x, y), WebFloatPoint(x, y),
        WebPointerProperties::Button::kLeft, 0,
        WebInputEvent::Modifiers::kLeftButtonDown, CurrentTimeTicksInSeconds());
    event.SetFrameScale(1);
    GetEventHandler().HandleMousePressEvent(event);
  }
