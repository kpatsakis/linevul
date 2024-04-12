void PDFiumEngine::DrawSelections(int progressive_index,
                                  pp::ImageData* image_data) {
  DCHECK_GE(progressive_index, 0);
  DCHECK_LT(static_cast<size_t>(progressive_index), progressive_paints_.size());
  DCHECK(image_data);

  int page_index = progressive_paints_[progressive_index].page_index;
  const pp::Rect& dirty_in_screen = progressive_paints_[progressive_index].rect;

  void* region = nullptr;
  int stride;
  GetRegion(dirty_in_screen.point(), image_data, &region, &stride);

  std::vector<pp::Rect> highlighted_rects;
  pp::Rect visible_rect = GetVisibleRect();
  for (auto& range : selection_) {
    if (range.page_index() != page_index)
      continue;

    const std::vector<pp::Rect>& rects = range.GetScreenRects(
        visible_rect.point(), current_zoom_, current_rotation_);
    for (const auto& rect : rects) {
      pp::Rect visible_selection = rect.Intersect(dirty_in_screen);
      if (visible_selection.IsEmpty())
        continue;

      visible_selection.Offset(-dirty_in_screen.point().x(),
                               -dirty_in_screen.point().y());
      Highlight(region, stride, visible_selection, &highlighted_rects);
    }
  }

  for (const auto& highlight : form_highlights_) {
    pp::Rect visible_selection = highlight.Intersect(dirty_in_screen);
    if (visible_selection.IsEmpty())
      continue;

    visible_selection.Offset(-dirty_in_screen.point().x(),
                             -dirty_in_screen.point().y());
    Highlight(region, stride, visible_selection, &highlighted_rects);
  }
  form_highlights_.clear();
}
