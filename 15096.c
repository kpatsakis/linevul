void Browser::OpenClearBrowsingDataDialog() {
  UserMetrics::RecordAction(UserMetricsAction("ClearBrowsingData_ShowDlg"),
                            profile_);
  ShowOptionsTab(chrome::kClearBrowserDataSubPage);
}
