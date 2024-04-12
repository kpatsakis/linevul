int PrintWebViewHelper::PrintPreviewContext::total_page_count() const {
  DCHECK(state_ != UNINITIALIZED);
  return total_page_count_;
}
