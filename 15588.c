void IsPinnedToTaskbarHelper::GetState(
    std::unique_ptr<service_manager::Connector> connector,
    const ErrorCallback& error_callback,
    const ResultCallback& result_callback) {
  new IsPinnedToTaskbarHelper(std::move(connector), error_callback,
                              result_callback);
}
