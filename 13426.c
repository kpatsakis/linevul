std::unique_ptr<APIPermission> UnpackPermissionWithArguments(
    base::StringPiece permission_name,
    base::StringPiece permission_arg,
    const std::string& permission_str,
    std::string* error) {
  std::unique_ptr<base::Value> permission_json =
      base::JSONReader::Read(permission_arg);
  if (!permission_json.get()) {
    *error = ErrorUtils::FormatErrorMessage(kInvalidParameter, permission_str);
    return nullptr;
  }

  std::unique_ptr<APIPermission> permission;

  const APIPermissionInfo* usb_device_permission_info =
      PermissionsInfo::GetInstance()->GetByID(APIPermission::kUsbDevice);
  if (permission_name == usb_device_permission_info->name()) {
    permission =
        std::make_unique<UsbDevicePermission>(usb_device_permission_info);
  } else {
    *error = kUnsupportedPermissionId;
    return nullptr;
  }

  CHECK(permission);
  if (!permission->FromValue(permission_json.get(), nullptr, nullptr)) {
    *error = ErrorUtils::FormatErrorMessage(kInvalidParameter, permission_str);
    return nullptr;
  }

  return permission;
}
