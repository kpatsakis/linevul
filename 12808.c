bool ShelfLayoutManager::ShouldChangeVisibilityAfterDrag(
    const ui::GestureEvent& gesture_in_screen) {
  if (visibility_state() == SHELF_VISIBLE)
    return false;

  if (gesture_in_screen.type() == ui::ET_GESTURE_SCROLL_END) {
    const float kDragHideThreshold = 0.4f;
    const gfx::Rect bounds = GetIdealBounds();
    const float drag_ratio =
        fabs(gesture_drag_amount_) /
        (shelf_->IsHorizontalAlignment() ? bounds.height() : bounds.width());

    return IsSwipingCorrectDirection() && drag_ratio > kDragHideThreshold;
  }

  if (gesture_in_screen.type() == ui::ET_SCROLL_FLING_START)
    return IsSwipingCorrectDirection();

  return false;
}
