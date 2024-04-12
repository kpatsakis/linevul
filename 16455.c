void Browser::ShowHistoryTab() {
  UserMetrics::RecordAction(UserMetricsAction("ShowHistory"), profile_);
  ShowSingletonTab(GURL(chrome::kChromeUIHistoryURL));
}
