void TabletEventConverterEvdev::DispatchMouseButton(const input_event& input) {
  if (!cursor_)
    return;

  unsigned int button;
  if (input.code == BTN_TOUCH)
    button = BTN_LEFT;
  else if (input.code == BTN_STYLUS2)
    button = BTN_RIGHT;
  else if (input.code == BTN_STYLUS)
    button = BTN_MIDDLE;
  else
    return;

  if (abs_value_dirty_) {
    UpdateCursor();
    abs_value_dirty_ = false;
  }

  bool down = input.value;

  dispatcher_->DispatchMouseButtonEvent(MouseButtonEventParams(
      input_device_.id, cursor_->GetLocation(), button, down,
      false /* allow_remap */, TimeDeltaFromInputEvent(input)));
}
