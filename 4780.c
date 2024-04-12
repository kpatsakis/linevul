SupervisedUserSettingsService* SupervisedUserService::GetSettingsService() {
  return SupervisedUserSettingsServiceFactory::GetForProfile(profile_);
}
