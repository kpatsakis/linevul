void LocalDOMWindow::scrollBy(const ScrollToOptions& scroll_to_options) const {
  if (!IsCurrentlyDisplayedInFrame())
    return;

  document()->UpdateStyleAndLayoutIgnorePendingStylesheets();

  LocalFrameView* view = GetFrame()->View();
  if (!view)
    return;

  Page* page = GetFrame()->GetPage();
  if (!page)
    return;

  if (GetFrame()->Loader().GetDocumentLoader()) {
    GetFrame()
        ->Loader()
        .GetDocumentLoader()
        ->GetInitialScrollState()
        .was_scrolled_by_js = true;
  }

  double x = 0.0;
  double y = 0.0;
  if (scroll_to_options.hasLeft())
    x = ScrollableArea::NormalizeNonFiniteScroll(scroll_to_options.left());
  if (scroll_to_options.hasTop())
    y = ScrollableArea::NormalizeNonFiniteScroll(scroll_to_options.top());

  ScrollableArea* viewport = view->LayoutViewportScrollableArea();
  ScrollOffset current_offset = viewport->GetScrollOffset();
  ScrollOffset scaled_delta(x * GetFrame()->PageZoomFactor(),
                            y * GetFrame()->PageZoomFactor());
  FloatPoint new_scaled_position = ScrollOffsetToPosition(
      scaled_delta + current_offset, viewport->ScrollOrigin());
  if (SnapCoordinator* coordinator = document()->GetSnapCoordinator()) {
    new_scaled_position = coordinator->GetSnapPositionForPoint(
        *document()->GetLayoutView(), new_scaled_position,
        scroll_to_options.hasLeft(), scroll_to_options.hasTop());
  }

  ScrollBehavior scroll_behavior = kScrollBehaviorAuto;
  ScrollableArea::ScrollBehaviorFromString(scroll_to_options.behavior(),
                                           scroll_behavior);
  viewport->SetScrollOffset(
      ScrollPositionToOffset(new_scaled_position, viewport->ScrollOrigin()),
      kProgrammaticScroll, scroll_behavior);
}
