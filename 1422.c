void BrowserView::MaybeStackBookmarkBarAtTop() {
  if (bookmark_bar_view_.get())
    bookmark_bar_view_->MaybeStackAtTop();
}
