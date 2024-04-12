IntRect PaintLayerScrollableArea::RectForVerticalScrollbar(
    const IntRect& border_box_rect) const {
  if (!HasVerticalScrollbar())
    return IntRect();

  const IntRect& scroll_corner = ScrollCornerRect();

  return IntRect(
      VerticalScrollbarStart(border_box_rect.X(), border_box_rect.MaxX()),
      border_box_rect.Y() + GetLayoutBox()->BorderTop().ToInt(),
      VerticalScrollbar()->ScrollbarThickness(),
      border_box_rect.Height() -
          (GetLayoutBox()->BorderTop() + GetLayoutBox()->BorderBottom())
              .ToInt() -
          scroll_corner.Height());
}
