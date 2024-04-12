std::string SupervisedUserService::GetCustodianName() const {
  std::string name = profile_->GetPrefs()->GetString(
      prefs::kSupervisedUserCustodianName);
#if defined(OS_CHROMEOS)
  if (name.empty() && !!user_manager::UserManager::Get()->GetActiveUser()) {
    name = base::UTF16ToUTF8(
        chromeos::ChromeUserManager::Get()
            ->GetSupervisedUserManager()
            ->GetManagerDisplayName(user_manager::UserManager::Get()
                                        ->GetActiveUser()
                                        ->GetAccountId()
                                        .GetUserEmail()));
  }
#endif
  return name.empty() ? GetCustodianEmailAddress() : name;
}
