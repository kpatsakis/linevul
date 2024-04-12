void PDFiumEngine::CalculateVisiblePages() {
  if (!doc_loader_)
    return;
  pending_pages_.clear();
  doc_loader_->ClearPendingRequests();

  std::vector<int> formerly_visible_pages;
  std::swap(visible_pages_, formerly_visible_pages);

  pp::Rect visible_rect(plugin_size_);
  for (int i = 0; i < static_cast<int>(pages_.size()); ++i) {
    if (visible_rect.Intersects(GetPageScreenRect(i))) {
      visible_pages_.push_back(i);
      if (CheckPageAvailable(i, &pending_pages_)) {
        auto it = std::find(formerly_visible_pages.begin(),
                            formerly_visible_pages.end(), i);
        if (it == formerly_visible_pages.end())
          client_->NotifyPageBecameVisible(pages_[i]->GetPageFeatures());
      }
    } else {
      if (defer_page_unload_) {
        deferred_page_unloads_.push_back(i);
      } else {
        pages_[i]->Unload();
      }

      if (static_cast<int>(i) == last_page_mouse_down_)
        last_page_mouse_down_ = -1;
    }
  }

  form_highlights_.clear();

  int most_visible_page = visible_pages_.empty() ? -1 : visible_pages_.front();
  if (most_visible_page != -1 && !pages_.empty() &&
      most_visible_page < static_cast<int>(pages_.size()) - 1) {
    pp::Rect rc_first =
        visible_rect.Intersect(GetPageScreenRect(most_visible_page));
    pp::Rect rc_next =
        visible_rect.Intersect(GetPageScreenRect(most_visible_page + 1));
    if (rc_next.height() > rc_first.height())
      most_visible_page++;
  }

  SetCurrentPage(most_visible_page);
}
