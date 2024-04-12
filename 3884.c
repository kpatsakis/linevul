bool MediaStreamManager::DoesMediaDeviceIDMatchHMAC(
    const std::string& salt,
    const url::Origin& security_origin,
    const std::string& device_guid,
    const std::string& raw_unique_id) {
  DCHECK(!raw_unique_id.empty());
  std::string guid_from_raw_device_id =
      GetHMACForMediaDeviceID(salt, security_origin, raw_unique_id);
  return guid_from_raw_device_id == device_guid;
}
