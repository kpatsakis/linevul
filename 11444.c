void PlatformSensorProviderWin::StopSensorThread() {
  if (sensor_thread_ && sensor_thread_->IsRunning())
    sensor_thread_->Stop();
}
