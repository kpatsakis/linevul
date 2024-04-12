void PaintLayerScrollableArea::ScrollbarFrameRectChanged() {
  if (!HasOverlayScrollbars())
    GetLayoutBox()->SetNeedsPaintPropertyUpdate();
}
