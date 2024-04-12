bool SupervisedUserService::AccessRequestsEnabled() {
  return FindEnabledPermissionRequestCreator(0) < permissions_creators_.size();
}
