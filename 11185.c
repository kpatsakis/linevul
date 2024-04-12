void UsbChooserContext::GetDevice(
    const std::string& guid,
    device::mojom::UsbDeviceRequest device_request,
    device::mojom::UsbDeviceClientPtr device_client) {
  EnsureConnectionWithDeviceManager();
  device_manager_->GetDevice(guid, std::move(device_request),
                             std::move(device_client));
}
