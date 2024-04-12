void FakeCentral::SetNextReadDescriptorResponse(
    uint16_t gatt_code,
    const base::Optional<std::vector<uint8_t>>& value,
    const std::string& descriptor_id,
    const std::string& characteristic_id,
    const std::string& service_id,
    const std::string& peripheral_address,
    SetNextReadDescriptorResponseCallback callback) {
  FakeRemoteGattDescriptor* fake_remote_gatt_descriptor =
      GetFakeRemoteGattDescriptor(peripheral_address, service_id,
                                  characteristic_id, descriptor_id);
  if (fake_remote_gatt_descriptor == nullptr) {
    std::move(callback).Run(false);
  }

  fake_remote_gatt_descriptor->SetNextReadResponse(gatt_code, value);
  std::move(callback).Run(true);
}
