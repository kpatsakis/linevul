bool UsbChooserContext::IsValidObject(const base::DictionaryValue& object) {
  return object.size() == 4 && object.HasKey(kDeviceNameKey) &&
         object.HasKey(kVendorIdKey) && object.HasKey(kProductIdKey) &&
         object.HasKey(kSerialNumberKey);
}
