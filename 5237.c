const BluetoothDevice* BluetoothAdapter::GetDevice(
    const std::string& address) const {
  std::string canonicalized_address =
      BluetoothDevice::CanonicalizeAddress(address);
  if (canonicalized_address.empty())
    return nullptr;

  auto iter = devices_.find(canonicalized_address);
  if (iter != devices_.end())
    return iter->second.get();

  return nullptr;
}
