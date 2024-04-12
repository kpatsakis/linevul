void AutoFillMetrics::Log(ServerQueryMetric metric) const {
  DCHECK(metric < NUM_SERVER_QUERY_METRICS);

  UMA_HISTOGRAM_ENUMERATION("AutoFill.ServerQueryResponse", metric,
                             NUM_SERVER_QUERY_METRICS);
 }
