void BrowserPolicyConnector::FetchDevicePolicy() {
#if defined(OS_CHROMEOS)
  if (device_data_store_.get()) {
    DCHECK(!device_data_store_->device_token().empty());
    device_data_store_->NotifyDeviceTokenChanged();
  }
#endif
}
