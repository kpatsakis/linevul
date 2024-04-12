std::vector<gfx::Image> GetImagesForAccounts(
    const std::vector<AccountInfo>& accounts,
    Profile* profile) {
  AccountTrackerService* tracker_service =
      AccountTrackerServiceFactory::GetForProfile(profile);
  std::vector<gfx::Image> images;
  for (auto account : accounts) {
    images.push_back(tracker_service->GetAccountImage(account.account_id));
  }
  return images;
}
