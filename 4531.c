void GestureSequence::AppendClickGestureEvent(const GesturePoint& point,
                                              Gestures* gestures) {
  gestures->push_back(linked_ptr<GestureEvent>(new GestureEvent(
      ui::ET_GESTURE_TAP,
      point.first_touch_position().x(),
      point.first_touch_position().y(),
      flags_,
      base::Time::FromDoubleT(point.last_touch_time()),
      0.f, 0.f)));
}
