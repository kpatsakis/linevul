DOMHighResTimeStamp PerformanceNavigationTiming::domContentLoadedEventEnd()
    const {
  const DocumentTiming* timing = GetDocumentTiming();
  if (!timing)
    return 0.0;
  return Performance::MonotonicTimeToDOMHighResTimeStamp(
      TimeOrigin(), timing->DomContentLoadedEventEnd(),
      false /* allow_negative_value */);
}
