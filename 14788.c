void RecordDaysSinceEnabledMetric(int days_since_enabled) {
  UMA_HISTOGRAM_CUSTOM_COUNTS("DataReductionProxy.DaysSinceEnabled",
                              days_since_enabled, 0, 365 * 10, 100);
}
