bool  PrintWebViewHelper::PrintPreviewContext::IsFinalPageRendered() const {
  return static_cast<size_t>(current_page_index_) == pages_to_render_.size();
}
