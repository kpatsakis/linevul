ScriptPromise BluetoothRemoteGATTCharacteristic::getDescriptors(
    ScriptState* scriptState,
    ExceptionState&) {
  return getDescriptorsImpl(
      scriptState, mojom::blink::WebBluetoothGATTQueryQuantity::MULTIPLE);
}
