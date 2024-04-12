OomInterventionMetrics OomInterventionImpl::GetCurrentMemoryMetrics() {
  return CrashMemoryMetricsReporterImpl::Instance().GetCurrentMemoryMetrics();
}
