void BluetoothRemoteGATTServer::GetPrimaryServicesCallback(
    mojom::blink::WebBluetoothGATTQueryQuantity quantity,
    ScriptPromiseResolver* resolver,
    mojom::blink::WebBluetoothResult result,
    Optional<Vector<mojom::blink::WebBluetoothRemoteGATTServicePtr>> services) {
  if (!resolver->getExecutionContext() ||
      resolver->getExecutionContext()->isContextDestroyed())
    return;

  if (!RemoveFromActiveAlgorithms(resolver)) {
    resolver->reject(
        DOMException::create(NetworkError, kGATTServerDisconnected));
    return;
  }

  if (result == mojom::blink::WebBluetoothResult::SUCCESS) {
    DCHECK(services);

    if (quantity == mojom::blink::WebBluetoothGATTQueryQuantity::SINGLE) {
      DCHECK_EQ(1u, services->size());
      resolver->resolve(m_device->getOrCreateRemoteGATTService(
          std::move(services.value()[0]), true /* isPrimary */,
          device()->id()));
      return;
    }

    HeapVector<Member<BluetoothRemoteGATTService>> gattServices;
    gattServices.reserveInitialCapacity(services->size());

    for (auto& service : services.value()) {
      gattServices.push_back(m_device->getOrCreateRemoteGATTService(
          std::move(service), true /* isPrimary */, device()->id()));
    }
    resolver->resolve(gattServices);
  } else {
    resolver->reject(BluetoothError::take(resolver, result));
  }
}
