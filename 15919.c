std::string SupervisedUserService::GetCustodianEmailAddress() const {
  std::string email = profile_->GetPrefs()->GetString(
      prefs::kSupervisedUserCustodianEmail);
#if defined(OS_CHROMEOS)
  if (email.empty() && !!user_manager::UserManager::Get()->GetActiveUser()) {
    email = chromeos::ChromeUserManager::Get()
                ->GetSupervisedUserManager()
                ->GetManagerDisplayEmail(user_manager::UserManager::Get()
                                             ->GetActiveUser()
                                             ->GetAccountId()
                                             .GetUserEmail());
  }
#endif
  return email;
}
