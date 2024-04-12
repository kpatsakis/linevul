void Document::AdjustFloatRectForScrollAndAbsoluteZoom(
    FloatRect& rect,
    LayoutObject& layout_object) {
  if (!View())
    return;

  LayoutRect visible_content_rect(View()->VisibleContentRect());
  rect.Move(-FloatSize(visible_content_rect.X().ToFloat(),
                       visible_content_rect.Y().ToFloat()));
  AdjustFloatRectForAbsoluteZoom(rect, layout_object);
}
