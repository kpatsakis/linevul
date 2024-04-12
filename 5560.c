void BrowserTabStripController::CloseTab(int model_index,
                                         CloseTabSource source) {
  hover_tab_selector_.CancelTabTransition();

  tabstrip_->PrepareForCloseAt(model_index, source);
  model_->CloseTabContentsAt(model_index,
                             TabStripModel::CLOSE_USER_GESTURE |
                             TabStripModel::CLOSE_CREATE_HISTORICAL_TAB);
}
