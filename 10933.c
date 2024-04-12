void BrowserView::HideDevToolsContainer() {
  devtools_focus_tracker_->FocusLastFocusedExternalView();
  devtools_container_->SetVisible(false);
  contents_split_->InvalidateLayout();
  Layout();
}
