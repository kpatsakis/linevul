void DeviceTokenFetcher::FetchTokenInternal() {
  DCHECK(state_ != STATE_TOKEN_AVAILABLE);
  if (!data_store_->has_auth_token() || data_store_->device_id().empty()) {
    return;
  }
  backend_.reset(service_->CreateBackend());
  em::DeviceRegisterRequest request;
  request.set_type(data_store_->policy_register_type());
  if (!data_store_->machine_id().empty())
    request.set_machine_id(data_store_->machine_id());
  if (!data_store_->machine_model().empty())
    request.set_machine_model(data_store_->machine_model());
  backend_->ProcessRegisterRequest(data_store_->gaia_token(),
                                   data_store_->oauth_token(),
                                   data_store_->device_id(),
                                   request, this);
}
