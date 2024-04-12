blink::mojom::WebBluetoothResult TranslateGATTErrorAndRecord(
    device::BluetoothRemoteGattService::GattErrorCode error_code,
    UMAGATTOperation operation) {
  switch (error_code) {
    case device::BluetoothRemoteGattService::GATT_ERROR_UNKNOWN:
      RecordGATTOperationOutcome(operation, UMAGATTOperationOutcome::UNKNOWN);
      return blink::mojom::WebBluetoothResult::GATT_UNKNOWN_ERROR;
    case device::BluetoothRemoteGattService::GATT_ERROR_FAILED:
      RecordGATTOperationOutcome(operation, UMAGATTOperationOutcome::FAILED);
      return blink::mojom::WebBluetoothResult::GATT_UNKNOWN_FAILURE;
    case device::BluetoothRemoteGattService::GATT_ERROR_IN_PROGRESS:
      RecordGATTOperationOutcome(operation,
                                 UMAGATTOperationOutcome::IN_PROGRESS);
      return blink::mojom::WebBluetoothResult::GATT_OPERATION_IN_PROGRESS;
    case device::BluetoothRemoteGattService::GATT_ERROR_INVALID_LENGTH:
      RecordGATTOperationOutcome(operation,
                                 UMAGATTOperationOutcome::INVALID_LENGTH);
      return blink::mojom::WebBluetoothResult::GATT_INVALID_ATTRIBUTE_LENGTH;
    case device::BluetoothRemoteGattService::GATT_ERROR_NOT_PERMITTED:
      RecordGATTOperationOutcome(operation,
                                 UMAGATTOperationOutcome::NOT_PERMITTED);
      return blink::mojom::WebBluetoothResult::GATT_NOT_PERMITTED;
    case device::BluetoothRemoteGattService::GATT_ERROR_NOT_AUTHORIZED:
      RecordGATTOperationOutcome(operation,
                                 UMAGATTOperationOutcome::NOT_AUTHORIZED);
      return blink::mojom::WebBluetoothResult::GATT_NOT_AUTHORIZED;
    case device::BluetoothRemoteGattService::GATT_ERROR_NOT_PAIRED:
      RecordGATTOperationOutcome(operation,
                                 UMAGATTOperationOutcome::NOT_PAIRED);
      return blink::mojom::WebBluetoothResult::GATT_NOT_PAIRED;
    case device::BluetoothRemoteGattService::GATT_ERROR_NOT_SUPPORTED:
      RecordGATTOperationOutcome(operation,
                                 UMAGATTOperationOutcome::NOT_SUPPORTED);
      return blink::mojom::WebBluetoothResult::GATT_NOT_SUPPORTED;
  }
  NOTREACHED();
  return blink::mojom::WebBluetoothResult::GATT_UNTRANSLATED_ERROR_CODE;
}
