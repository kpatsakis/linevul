void PlatformSensorProviderLinux::SetSensorDeviceManagerForTesting(
    std::unique_ptr<SensorDeviceManager> sensor_device_manager) {
  DCHECK_CALLED_ON_VALID_THREAD(thread_checker_);
  Shutdown();
  sensor_device_manager_ = std::move(sensor_device_manager);
}
