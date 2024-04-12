void BluetoothDeviceChooserController::PopulateConnectedDevices() {
  for (const device::BluetoothDevice* device : adapter_->GetDevices()) {
    if (device->IsGattConnected()) {
      AddFilteredDevice(*device);
    }
  }
}
