void Browser::OpenClearBrowsingDataDialog() {
  UserMetrics::RecordAction(UserMetricsAction("ClearBrowsingData_ShowDlg"),
                            profile_);
  if (!CommandLine::ForCurrentProcess()->HasSwitch(
      switches::kDisableTabbedOptions)) {
    ShowOptionsTab(
        chrome::kAdvancedOptionsSubPage + std::string(kHashMark) +
        chrome::kClearBrowserDataSubPage);
  } else {
    window_->ShowClearBrowsingDataDialog();
  }
}
