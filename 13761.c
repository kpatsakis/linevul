void PlatformSensorProviderWin::CreateSensorThread() {
  if (!sensor_thread_)
    sensor_thread_ = std::make_unique<SensorThread>();
}
