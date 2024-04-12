void Browser::CloseWindow() {
  UserMetrics::RecordAction(UserMetricsAction("CloseWindow"), profile_);
  window_->Close();
}
