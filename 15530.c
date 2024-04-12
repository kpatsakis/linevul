void CSSStyleSheet::StartLoadingDynamicSheet() {
  SetLoadCompleted(false);
  owner_node_->StartLoadingDynamicSheet();
}
