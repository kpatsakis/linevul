void Browser::FocusNextPane() {
  UserMetrics::RecordAction(UserMetricsAction("FocusNextPane"), profile_);
  window_->RotatePaneFocus(true);
}
