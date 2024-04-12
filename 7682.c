bool CanStorePersistentEntry(const device::mojom::UsbDeviceInfo& device_info) {
  return !device_info.serial_number->empty();
}
