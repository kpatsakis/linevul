void WebBluetoothServiceImpl::RemoteServerConnect(
    const WebBluetoothDeviceId& device_id,
    blink::mojom::WebBluetoothServerClientAssociatedPtrInfo client,
    RemoteServerConnectCallback callback) {
  DCHECK_CURRENTLY_ON(BrowserThread::UI);

  const CacheQueryResult query_result = QueryCacheForDevice(device_id);

  if (query_result.outcome != CacheQueryOutcome::SUCCESS) {
    RecordConnectGATTOutcome(query_result.outcome);
    std::move(callback).Run(query_result.GetWebResult());
    return;
  }

  if (connected_devices_->IsConnectedToDeviceWithId(device_id)) {
    DVLOG(1) << "Already connected.";
    std::move(callback).Run(blink::mojom::WebBluetoothResult::SUCCESS);
    return;
  }

  const base::TimeTicks start_time = base::TimeTicks::Now();
  blink::mojom::WebBluetoothServerClientAssociatedPtr
      web_bluetooth_server_client;
  web_bluetooth_server_client.Bind(std::move(client));

  auto copyable_callback = base::AdaptCallbackForRepeating(std::move(callback));
  query_result.device->CreateGattConnection(
      base::Bind(&WebBluetoothServiceImpl::OnCreateGATTConnectionSuccess,
                 weak_ptr_factory_.GetWeakPtr(), device_id, start_time,
                 base::Passed(&web_bluetooth_server_client), copyable_callback),
      base::Bind(&WebBluetoothServiceImpl::OnCreateGATTConnectionFailed,
                 weak_ptr_factory_.GetWeakPtr(), start_time,
                 copyable_callback));
}
