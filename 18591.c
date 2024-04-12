void FakeCrosDisksClient::NotifyRenameCompleted(
    RenameError error_code,
    const std::string& device_path) {
  for (auto& observer : observer_list_)
    observer.OnRenameCompleted(error_code, device_path);
}
