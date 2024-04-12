std::string BluetoothAdapterChromeOS::GetName() const {
  if (!IsPresent())
    return std::string();

  BluetoothAdapterClient::Properties* properties =
      DBusThreadManager::Get()->GetBluetoothAdapterClient()->
          GetProperties(object_path_);
  DCHECK(properties);

  return properties->alias.value();
}
