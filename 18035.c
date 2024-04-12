PlatformSensorFusion::~PlatformSensorFusion() {
  for (const auto& pair : source_sensors_)
    pair.second->RemoveClient(this);
}
