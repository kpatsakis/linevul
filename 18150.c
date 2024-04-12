void Browser::CloseWindow() {
  UserMetrics::RecordAction(UserMetricsAction("CloseWindow"));
  window_->Close();
}
