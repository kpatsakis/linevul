UkmPageLoadMetricsObserver::ObservePolicy UkmPageLoadMetricsObserver::OnCommit(
    content::NavigationHandle* navigation_handle,
    ukm::SourceId source_id) {
  const net::HttpResponseHeaders* response_headers =
      navigation_handle->GetResponseHeaders();
  if (response_headers)
    http_response_code_ = response_headers->response_code();
  page_transition_ = navigation_handle->GetPageTransition();
  was_cached_ = navigation_handle->WasResponseCached();
  navigation_start_ = navigation_handle->NavigationStart();
  return CONTINUE_OBSERVING;
}
