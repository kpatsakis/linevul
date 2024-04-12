void PaintLayerScrollableArea::UpdateScrollDimensions() {
  LayoutRect new_overflow_rect = GetLayoutBox()->LayoutOverflowRect();
  GetLayoutBox()->FlipForWritingMode(new_overflow_rect);

  new_overflow_rect.Unite(
      LayoutRect(new_overflow_rect.Location(),
                 LayoutContentRect(kExcludeScrollbars).Size()));

  if (overflow_rect_.Size() != new_overflow_rect.Size())
    ContentsResized();
  overflow_rect_ = new_overflow_rect;
  UpdateScrollOrigin();
}
