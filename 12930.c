bool BluetoothSocketListenUsingRfcommFunction::CreateParams() {
  params_ = bluetooth_socket::ListenUsingRfcomm::Params::Create(*args_);
  return params_ != nullptr;
}
