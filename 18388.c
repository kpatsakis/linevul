void Browser::CreateHistoricalTab(TabContentsWrapper* contents) {
  if (!profile() || profile()->IsOffTheRecord() ||
      !profile()->GetTabRestoreService()) {
    return;
  }

  if (CanSupportWindowFeature(FEATURE_TABSTRIP)) {
    profile()->GetTabRestoreService()->CreateHistoricalTab(
        &contents->controller(),
        tab_handler_->GetTabStripModel()->GetIndexOfTabContents(contents));
  }
}
