void WebBluetoothServiceImpl::RequestDeviceImpl(
    blink::mojom::WebBluetoothRequestDeviceOptionsPtr options,
    RequestDeviceCallback callback,
    device::BluetoothAdapter* adapter) {
  device_chooser_controller_.reset();

  device_chooser_controller_.reset(
      new BluetoothDeviceChooserController(this, render_frame_host_, adapter));

  auto copyable_callback = base::AdaptCallbackForRepeating(std::move(callback));
  device_chooser_controller_->GetDevice(
      std::move(options),
      base::Bind(&WebBluetoothServiceImpl::OnGetDeviceSuccess,
                 weak_ptr_factory_.GetWeakPtr(), copyable_callback),
      base::Bind(&WebBluetoothServiceImpl::OnGetDeviceFailed,
                 weak_ptr_factory_.GetWeakPtr(), copyable_callback));
}
