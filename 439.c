void WebBluetoothServiceImpl::GattCharacteristicValueChanged(
    device::BluetoothAdapter* adapter,
    device::BluetoothRemoteGattCharacteristic* characteristic,
    const std::vector<uint8_t>& value) {
  if (!base::ContainsKey(characteristic_id_to_service_id_,
                         characteristic->GetIdentifier())) {
    return;
  }

  if (!base::ThreadTaskRunnerHandle::Get()->PostTask(
          FROM_HERE,
          base::BindOnce(
              &WebBluetoothServiceImpl::NotifyCharacteristicValueChanged,
              weak_ptr_factory_.GetWeakPtr(), characteristic->GetIdentifier(),
              value))) {
    LOG(WARNING) << "No TaskRunner.";
  }
}
