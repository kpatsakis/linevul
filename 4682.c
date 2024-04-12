void BrowserView::FocusBookmarksToolbar() {
  if (active_bookmark_bar_ && bookmark_bar_view_->visible())
    bookmark_bar_view_->SetPaneFocus(bookmark_bar_view_.get());
}
