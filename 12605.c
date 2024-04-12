bool GestureSequence::Click(const TouchEvent& event,
    const GesturePoint& point, Gestures* gestures) {
  DCHECK(state_ == GS_PENDING_SYNTHETIC_CLICK);
  if (point.IsInClickWindow(event)) {
    AppendClickGestureEvent(point, gestures);
    if (point.IsInDoubleClickWindow(event))
      AppendDoubleClickGestureEvent(point, gestures);
    return true;
  }
  return false;
}
