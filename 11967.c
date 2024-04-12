OxideQQuickTouchSelectionController* OxideQQuickWebView::touchSelectionController() {
  Q_D(OxideQQuickWebView);

  return d->contents_view_->touchSelectionController();
}
