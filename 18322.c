bool BrowserWindowGtk::IsBookmarkBarAnimating() const {
  if (IsBookmarkBarSupported() && bookmark_bar_->IsAnimating())
    return true;
  return false;
}
