void BrowserView::BookmarkBarStateChanged(
    BookmarkBar::AnimateChangeType change_type) {
  if (bookmark_bar_view_.get()) {
    bookmark_bar_view_->SetBookmarkBarState(
        browser_->bookmark_bar_state(), change_type,
        browser_->search_model()->mode());
  }
  if (MaybeShowBookmarkBar(GetActiveTabContents()))
    Layout();
}
