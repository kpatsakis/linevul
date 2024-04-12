void AutofillManager::set_metric_logger(
    const AutofillMetrics* metric_logger) {
  metric_logger_.reset(metric_logger);
}
