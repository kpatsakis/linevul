void PlatformSensor::NotifySensorError() {
  for (auto& client : clients_)
    client.OnSensorError();
}
