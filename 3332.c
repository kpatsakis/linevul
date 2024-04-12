int PaintLayerScrollableArea::HorizontalScrollbarHeight(
    OverlayScrollbarClipBehavior overlay_scrollbar_clip_behavior) const {
  if (!HasHorizontalScrollbar())
    return 0;
  if (overlay_scrollbar_clip_behavior ==
          kIgnorePlatformAndCSSOverlayScrollbarSize &&
      GetLayoutBox()->StyleRef().OverflowX() == EOverflow::kOverlay) {
    return 0;
  }
  if ((overlay_scrollbar_clip_behavior == kIgnorePlatformOverlayScrollbarSize ||
       overlay_scrollbar_clip_behavior ==
           kIgnorePlatformAndCSSOverlayScrollbarSize ||
       !HorizontalScrollbar()->ShouldParticipateInHitTesting()) &&
      HorizontalScrollbar()->IsOverlayScrollbar()) {
    return 0;
  }
  return HorizontalScrollbar()->ScrollbarThickness();
}
