void EventConverterEvdevImpl::ReleaseMouseButtons() {
  base::TimeDelta timestamp = ui::EventTimeForNow();
  for (int code = BTN_MOUSE; code < BTN_JOYSTICK; ++code)
    OnButtonChange(code, false /* down */, timestamp);
}
