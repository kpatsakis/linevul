bool PlatformSensorWin::CheckSensorConfiguration(
    const PlatformSensorConfiguration& configuration) {
  DCHECK(task_runner_->BelongsToCurrentThread());
  double minimal_reporting_interval_ms =
      sensor_reader_->GetMinimalReportingIntervalMs();
  if (minimal_reporting_interval_ms == 0)
    return true;
  double max_frequency =
      base::Time::kMillisecondsPerSecond / minimal_reporting_interval_ms;
  return configuration.frequency() <= max_frequency;
}
