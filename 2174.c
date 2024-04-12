void OomInterventionTabHelper::StopMonitoring() {
  if (OomInterventionConfig::GetInstance()->should_detect_in_renderer()) {
    ResetInterfaces();
  } else {
    subscription_.reset();
  }
}
