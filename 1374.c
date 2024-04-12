bool UsbChooserContext::HasDevicePermission(
    const GURL& requesting_origin,
    const GURL& embedding_origin,
    scoped_refptr<const device::UsbDevice> device) {
  if (!device)
    return false;

  device::mojom::UsbDeviceInfoPtr device_info =
      device::mojom::UsbDeviceInfo::From(*device);
  DCHECK(device_info);

  return HasDevicePermission(requesting_origin, embedding_origin, *device_info);
}
