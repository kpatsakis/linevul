void RecordPermissionRevocation(WebUsbPermissionRevoked kind) {
  UMA_HISTOGRAM_ENUMERATION("WebUsb.PermissionRevoked", kind,
                            WEBUSB_PERMISSION_REVOKED_MAX);
}
