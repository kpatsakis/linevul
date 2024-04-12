Scrollbar* PaintLayerScrollableArea::ScrollbarManager::CreateScrollbar(
    ScrollbarOrientation orientation) {
  DCHECK(orientation == kHorizontalScrollbar ? !h_bar_is_attached_
                                             : !v_bar_is_attached_);
  Scrollbar* scrollbar = nullptr;
  const LayoutObject& style_source =
      ScrollbarStyleSource(*ScrollableArea()->GetLayoutBox());
  bool has_custom_scrollbar_style =
      style_source.StyleRef().HasPseudoStyle(kPseudoIdScrollbar);
  if (has_custom_scrollbar_style) {
    DCHECK(style_source.GetNode() && style_source.GetNode()->IsElementNode());
    scrollbar = LayoutScrollbar::CreateCustomScrollbar(
        ScrollableArea(), orientation, ToElement(style_source.GetNode()));
  } else {
    ScrollbarControlSize scrollbar_size = kRegularScrollbar;
    if (style_source.StyleRef().HasAppearance()) {
      scrollbar_size = LayoutTheme::GetTheme().ScrollbarControlSizeForPart(
          style_source.StyleRef().Appearance());
    }
    scrollbar = Scrollbar::Create(ScrollableArea(), orientation, scrollbar_size,
                                  &ScrollableArea()
                                       ->GetLayoutBox()
                                       ->GetFrame()
                                       ->GetPage()
                                       ->GetChromeClient());
  }
  ScrollableArea()->GetLayoutBox()->GetDocument().View()->AddScrollbar(
      scrollbar);
  return scrollbar;
}
