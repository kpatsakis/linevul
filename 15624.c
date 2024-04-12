base::DictionaryValue DeviceInfoToDictValue(
    const device::mojom::UsbDeviceInfo& device_info) {
  base::DictionaryValue device_dict;
  device_dict.SetKey(kDeviceNameKey,
                     device_info.product_name
                         ? base::Value(*device_info.product_name)
                         : base::Value(""));

  if (!CanStorePersistentEntry(device_info)) {
    device_dict.SetKey(kGuidKey, base::Value(device_info.guid));
    return device_dict;
  }
  device_dict.SetKey(kVendorIdKey, base::Value(device_info.vendor_id));
  device_dict.SetKey(kProductIdKey, base::Value(device_info.product_id));
  device_dict.SetKey(kSerialNumberKey,
                     device_info.serial_number
                         ? base::Value(*device_info.serial_number)
                         : base::Value(""));
  return device_dict;
}
