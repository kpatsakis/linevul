IntRect PaintLayerScrollableArea::PaintLayerScrollableArea::CornerRect(
    const IntRect& bounds) const {
  int horizontal_thickness;
  int vertical_thickness;
  if (!VerticalScrollbar() && !HorizontalScrollbar()) {
    horizontal_thickness = GetPageScrollbarTheme().ScrollbarThickness();
    vertical_thickness = horizontal_thickness;
  } else if (VerticalScrollbar() && !HorizontalScrollbar()) {
    horizontal_thickness = VerticalScrollbar()->ScrollbarThickness();
    vertical_thickness = horizontal_thickness;
  } else if (HorizontalScrollbar() && !VerticalScrollbar()) {
    vertical_thickness = HorizontalScrollbar()->ScrollbarThickness();
    horizontal_thickness = vertical_thickness;
  } else {
    horizontal_thickness = VerticalScrollbar()->ScrollbarThickness();
    vertical_thickness = HorizontalScrollbar()->ScrollbarThickness();
  }
  return IntRect(CornerStart(*GetLayoutBox(), bounds.X(), bounds.MaxX(),
                             horizontal_thickness),
                 bounds.MaxY() - vertical_thickness -
                     GetLayoutBox()->StyleRef().BorderBottomWidth(),
                 horizontal_thickness, vertical_thickness);
}
