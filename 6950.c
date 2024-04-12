bool GestureSequence::PinchStart(const TouchEvent& event,
    const GesturePoint& point, Gestures* gestures) {
  DCHECK(state_ == GS_SCROLL ||
         state_ == GS_PENDING_SYNTHETIC_CLICK);
  AppendTapDownGestureEvent(point, gestures);

  pinch_distance_current_ = points_[0].Distance(points_[1]);
  pinch_distance_start_ = pinch_distance_current_;
  AppendPinchGestureBegin(points_[0], points_[1], gestures);

  if (state_ == GS_PENDING_SYNTHETIC_CLICK) {
    gfx::Point center = points_[0].last_touch_position().Middle(
        points_[1].last_touch_position());
    AppendScrollGestureBegin(point, center, gestures);
  }

  return true;
}
