ChromePasswordManagerClient::GetMetricsRecorder() {
  if (!metrics_recorder_) {
    metrics_recorder_.emplace(GetUkmSourceId(), GetMainFrameURL());
  }
  return base::OptionalOrNullptr(metrics_recorder_);
}
