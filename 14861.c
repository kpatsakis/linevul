void PlatformSensorAmbientLightMac::IOServiceCallback(void* context,
                                                      io_service_t service,
                                                      natural_t message_type,
                                                      void* message_argument) {
  PlatformSensorAmbientLightMac* sensor =
      static_cast<PlatformSensorAmbientLightMac*>(context);
  if (!sensor->ReadAndUpdate()) {
    sensor->NotifySensorError();
    sensor->StopSensor();
  }
}
