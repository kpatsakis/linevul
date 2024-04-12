uint16 BluetoothDeviceChromeOS::GetProductID() const {
  uint16 product_id  = 0;
  ParseModalias(object_path_, NULL, &product_id, NULL);
  return product_id;
}
