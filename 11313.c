void BluetoothRemoteGATTCharacteristic::contextDestroyed(ExecutionContext*) {
  notifyCharacteristicObjectRemoved();
}
