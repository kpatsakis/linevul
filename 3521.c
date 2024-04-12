bool GestureSequence::ScrollEnd(const TouchEvent& event,
    GesturePoint& point, Gestures* gestures) {
  DCHECK(state_ == GS_SCROLL);
  if (point.IsInFlickWindow(event)) {
    AppendScrollGestureEnd(point, point.last_touch_position(), gestures,
        point.XVelocity(), point.YVelocity());
  } else {
    AppendScrollGestureEnd(point, point.last_touch_position(), gestures,
        0.f, 0.f);
  }
  return true;
}
