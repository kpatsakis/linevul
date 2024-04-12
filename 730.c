void PaintLayerScrollableArea::UpdateAfterOverflowRecalc() {
  UpdateScrollDimensions();
  UpdateScrollbarProportions();

  bool needs_horizontal_scrollbar;
  bool needs_vertical_scrollbar;
  ComputeScrollbarExistence(needs_horizontal_scrollbar,
                            needs_vertical_scrollbar);

  bool horizontal_scrollbar_should_change =
      needs_horizontal_scrollbar != HasHorizontalScrollbar();
  bool vertical_scrollbar_should_change =
      needs_vertical_scrollbar != HasVerticalScrollbar();

  if ((GetLayoutBox()->HasAutoHorizontalScrollbar() &&
       horizontal_scrollbar_should_change) ||
      (GetLayoutBox()->HasAutoVerticalScrollbar() &&
       vertical_scrollbar_should_change)) {
    GetLayoutBox()->SetNeedsLayoutAndFullPaintInvalidation(
        layout_invalidation_reason::kUnknown);
  }

  ClampScrollOffsetAfterOverflowChange();
}
