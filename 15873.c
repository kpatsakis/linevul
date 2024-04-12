FakePlatformSensorProvider::FakePlatformSensorProvider() {
  ON_CALL(*this, DoCreateSensorInternal(_, _, _))
      .WillByDefault(Invoke(
          [](mojom::SensorType, scoped_refptr<PlatformSensor> sensor,
             const PlatformSensorProvider::CreateSensorCallback& callback) {
            callback.Run(std::move(sensor));
          }));
}
