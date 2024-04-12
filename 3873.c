void CorePageLoadMetricsObserver::OnLoadEventStart(
    const page_load_metrics::PageLoadTiming& timing,
    const page_load_metrics::PageLoadExtraInfo& info) {
  if (WasStartedInForegroundOptionalEventInForeground(timing.load_event_start,
                                                      info)) {
    PAGE_LOAD_HISTOGRAM(internal::kHistogramLoadImmediate,
                        timing.load_event_start.value());
  } else {
    PAGE_LOAD_HISTOGRAM(internal::kBackgroundHistogramLoadImmediate,
                        timing.load_event_start.value());
  }
}
