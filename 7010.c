 void Bluetooth::RequestDeviceCallback(
     ScriptPromiseResolver* resolver,
     mojom::blink::WebBluetoothResult result,
    mojom::blink::WebBluetoothDevicePtr device) {
  if (!resolver->GetExecutionContext() ||
      resolver->GetExecutionContext()->IsContextDestroyed()) {
    return;
  }

  if (result == mojom::blink::WebBluetoothResult::SUCCESS) {
    BluetoothDevice* bluetooth_device = GetBluetoothDeviceRepresentingDevice(
        std::move(device), resolver->GetExecutionContext());
    resolver->Resolve(bluetooth_device);
  } else {
    resolver->Reject(BluetoothError::CreateDOMException(result));
  }
}
