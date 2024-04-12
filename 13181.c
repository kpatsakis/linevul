ScriptPromise BluetoothRemoteGATTService::getCharacteristic(
    ScriptState* scriptState,
    const StringOrUnsignedLong& characteristic,
    ExceptionState& exceptionState) {
  String characteristicUUID =
      BluetoothUUID::getCharacteristic(characteristic, exceptionState);
  if (exceptionState.hadException())
    return exceptionState.reject(scriptState);

  return getCharacteristicsImpl(
      scriptState, mojom::blink::WebBluetoothGATTQueryQuantity::SINGLE,
      characteristicUUID);
}
