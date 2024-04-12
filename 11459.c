BluetoothAdapter::~BluetoothAdapter() {
  if (set_powered_callbacks_)
    set_powered_callbacks_->error_callback.Run();
}
