void PopulatePolicyHandlerParameters(PolicyHandlerParameters* parameters) {
#if defined(OS_CHROMEOS)
  if (user_manager::UserManager::IsInitialized()) {
    const user_manager::User* user =
        user_manager::UserManager::Get()->GetActiveUser();
    if (user)
      parameters->user_id_hash = user->username_hash();
  }
#endif
}
