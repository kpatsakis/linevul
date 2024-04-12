void ScrollableShelfView::ScrollToYOffset(float y_target_offset,
                                          bool animating) {
  y_target_offset = CalculateClampedScrollOffset(y_target_offset);
  const int old_y = scroll_offset_.y();
  scroll_offset_.set_y(y_target_offset);
  Layout();
  const float diff = y_target_offset - old_y;
  if (animating)
    StartShelfScrollAnimation(diff);
}
