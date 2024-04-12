bool PaintLayerScrollableArea::HasVerticalOverflow() const {
  LayoutUnit client_height =
      LayoutContentRect(kIncludeScrollbars).Height() -
      HorizontalScrollbarHeight(kIgnorePlatformAndCSSOverlayScrollbarSize);
  LayoutUnit scroll_height(ScrollHeight());
  LayoutUnit box_y = GetLayoutBox()->Location().Y();
  return SnapSizeToPixel(scroll_height, box_y) >
         SnapSizeToPixel(client_height, box_y);
}
