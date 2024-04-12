PlatformSensorAmbientLightMac::GetDefaultConfiguration() {
  PlatformSensorConfiguration default_configuration;
  default_configuration.set_frequency(
      SensorTraits<SensorType::AMBIENT_LIGHT>::kDefaultFrequency);
  return default_configuration;
}
