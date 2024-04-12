void WebBluetoothServiceImpl::OnStartNotifySessionSuccess(
    blink::mojom::WebBluetoothCharacteristicClientAssociatedPtr client,
    RemoteCharacteristicStartNotificationsCallback callback,
    std::unique_ptr<device::BluetoothGattNotifySession> notify_session) {
  DCHECK_CURRENTLY_ON(BrowserThread::UI);
  std::string characteristic_instance_id =
      notify_session->GetCharacteristicIdentifier();

  std::move(callback).Run(blink::mojom::WebBluetoothResult::SUCCESS);
  auto gatt_notify_session_and_client =
      std::make_unique<GATTNotifySessionAndCharacteristicClient>(
          std::move(notify_session), std::move(client));
  characteristic_id_to_notify_session_[characteristic_instance_id] =
      std::move(gatt_notify_session_and_client);
}
