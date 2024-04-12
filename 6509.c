PlatformSensorAccelerometerMac::GetDefaultConfiguration() {
  return PlatformSensorConfiguration(
      SensorTraits<SensorType::ACCELEROMETER>::kDefaultFrequency);
}
