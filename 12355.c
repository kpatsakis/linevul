 void UsbChooserContext::EnsureConnectionWithDeviceManager() {
   if (device_manager_)
    return;

  device_manager_instance_ = std::make_unique<device::usb::DeviceManagerImpl>();
  device_manager_instance_->AddBinding(mojo::MakeRequest(&device_manager_));
  device_manager_.set_connection_error_handler(
      base::BindOnce(&UsbChooserContext::OnDeviceManagerConnectionError,
                     base::Unretained(this)));

  DCHECK(!client_binding_);
  device::mojom::UsbDeviceManagerClientAssociatedPtrInfo client;
  client_binding_.Bind(mojo::MakeRequest(&client));
  device_manager_->SetClient(std::move(client));
}
