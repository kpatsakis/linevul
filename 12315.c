int GetSystemMetricsInDIP(int metric) {
  return static_cast<int>(GetSystemMetrics(metric) /
      GetDeviceScaleFactor() + 0.5);
}
