void WebBluetoothServiceImpl::SetClientConnectionErrorHandler(
    base::OnceClosure closure) {
  binding_.set_connection_error_handler(std::move(closure));
}
