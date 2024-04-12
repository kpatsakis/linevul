void BrowserTabStripController::CreateNewTab() {
  model_->delegate()->AddBlankTabAt(-1, true);
}
