static LayoutPoint CornerPointOfRect(LayoutRect rect, Corner which_corner) {
  switch (which_corner) {
    case Corner::kTopLeft:
      return rect.MinXMinYCorner();
    case Corner::kTopRight:
      return rect.MaxXMinYCorner();
  }
  NOTREACHED();
  return LayoutPoint();
}
