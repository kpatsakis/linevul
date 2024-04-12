void Document::AdjustFloatQuadsForScrollAndAbsoluteZoom(
    Vector<FloatQuad>& quads,
    const LayoutObject& layout_object) const {
  if (!View())
    return;

  LayoutRect visible_content_rect(View()->VisibleContentRect());
  for (size_t i = 0; i < quads.size(); ++i) {
    quads[i].Move(-FloatSize(visible_content_rect.X().ToFloat(),
                             visible_content_rect.Y().ToFloat()));
    AdjustForAbsoluteZoom::AdjustFloatQuad(quads[i], layout_object);
  }
}
