void PDFiumEngine::SelectionChangeInvalidator::GetVisibleSelectionsScreenRects(
    std::vector<pp::Rect>* rects) {
  pp::Rect visible_rect = engine_->GetVisibleRect();
  for (auto& range : engine_->selection_) {
    int page_index = range.page_index();
    if (!engine_->IsPageVisible(page_index))
      continue;  // This selection is on a page that's not currently visible.

    std::vector<pp::Rect> selection_rects =
        range.GetScreenRects(
            visible_rect.point(),
            engine_->current_zoom_,
            engine_->current_rotation_);
    rects->insert(rects->end(), selection_rects.begin(), selection_rects.end());
  }
}
