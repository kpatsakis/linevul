void BluetoothAdapterChromeOS::StartDiscovering(
    const base::Closure& callback,
    const ErrorCallback& error_callback) {
  DBusThreadManager::Get()->GetBluetoothAdapterClient()->
      StartDiscovery(
          object_path_,
          base::Bind(&BluetoothAdapterChromeOS::OnStartDiscovery,
                     weak_ptr_factory_.GetWeakPtr(),
                     callback),
          base::Bind(&BluetoothAdapterChromeOS::OnStartDiscoveryError,
                     weak_ptr_factory_.GetWeakPtr(),
                     error_callback));
}
