void BluetoothRemoteGATTServer::ConnectCallback(
    ScriptPromiseResolver* resolver,
    mojom::blink::WebBluetoothResult result) {
  if (!resolver->getExecutionContext() ||
      resolver->getExecutionContext()->isContextDestroyed())
    return;

  if (result == mojom::blink::WebBluetoothResult::SUCCESS) {
    setConnected(true);
    resolver->resolve(this);
  } else {
    resolver->reject(BluetoothError::take(resolver, result));
  }
}
