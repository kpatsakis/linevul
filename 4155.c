bool WebBluetoothServiceImpl::IsDevicePaired(
    const std::string& device_address) {
  return allowed_devices().GetDeviceId(device_address) != nullptr;
}
