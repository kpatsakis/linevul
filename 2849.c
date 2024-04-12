void ScrollableShelfView::ScrollByYOffset(float y_offset, bool animating) {
  ScrollToYOffset(scroll_offset_.y() + y_offset, animating);
}
