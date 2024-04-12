void BluetoothAdapter::NotifyGattServicesDiscovered(BluetoothDevice* device) {
  DCHECK(device->GetAdapter() == this);

  for (auto& observer : observers_)
    observer.GattServicesDiscovered(this, device);
}
