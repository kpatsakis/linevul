void OomInterventionTabHelper::OnHighMemoryUsage() {
  auto* config = OomInterventionConfig::GetInstance();
  if (config->is_renderer_pause_enabled() ||
      config->is_navigate_ads_enabled()) {
    NearOomReductionInfoBar::Show(web_contents(), this);
    intervention_state_ = InterventionState::UI_SHOWN;
    if (!last_navigation_timestamp_.is_null()) {
      base::TimeDelta time_since_last_navigation =
          base::TimeTicks::Now() - last_navigation_timestamp_;
      UMA_HISTOGRAM_COUNTS_1M(
          "Memory.Experimental.OomIntervention."
          "RendererTimeSinceLastNavigationAtIntervention",
          time_since_last_navigation.InSeconds());
    }
  }
  near_oom_detected_time_ = base::TimeTicks::Now();
  renderer_detection_timer_.AbandonAndStop();
}
