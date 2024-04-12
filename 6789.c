void Browser::FocusChromeOSStatus() {
  UserMetrics::RecordAction(UserMetricsAction("FocusChromeOSStatus"));
  window_->FocusChromeOSStatus();
}
