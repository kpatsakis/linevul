bool GestureSequence::ScrollUpdate(const TouchEvent& event,
    const GesturePoint& point, Gestures* gestures) {
  DCHECK(state_ == GS_SCROLL);
  if (!point.DidScroll(event, 0))
    return false;
  AppendScrollGestureUpdate(point, point.last_touch_position(), gestures);
  return true;
}
