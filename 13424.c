void UserCloudPolicyManagerChromeOS::Connect(
    PrefService* local_state,
    DeviceManagementService* device_management_service,
    scoped_refptr<net::URLRequestContextGetter> system_request_context,
    UserAffiliation user_affiliation) {
  DCHECK(device_management_service);
  DCHECK(local_state);
  local_state_ = local_state;
  scoped_refptr<net::URLRequestContextGetter> request_context;
  if (system_request_context) {
    request_context = new SystemPolicyRequestContext(
        system_request_context, GetUserAgent());
  }
  scoped_ptr<CloudPolicyClient> cloud_policy_client(
      new CloudPolicyClient(std::string(), std::string(),
                            kPolicyVerificationKeyHash, user_affiliation,
                            NULL, device_management_service,
                            request_context));
  core()->Connect(cloud_policy_client.Pass());
  client()->AddObserver(this);

  external_data_manager_->Connect(request_context);

  CreateComponentCloudPolicyService(component_policy_cache_path_,
                                    request_context);

  if (service()->IsInitializationComplete()) {
    OnInitializationCompleted(service());
  } else {
    service()->AddObserver(this);
  }
}
