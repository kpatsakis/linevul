void WallpaperManager::InitializeRegisteredDeviceWallpaper() {
  if (user_manager::UserManager::Get()->IsUserLoggedIn())
    return;

  bool disable_boot_animation =
      GetCommandLine()->HasSwitch(switches::kDisableBootAnimation);
  bool show_users = true;
  bool result = CrosSettings::Get()->GetBoolean(
      kAccountsPrefShowUserNamesOnSignIn, &show_users);
  DCHECK(result) << "Unable to fetch setting "
                 << kAccountsPrefShowUserNamesOnSignIn;
  const user_manager::UserList& users =
      user_manager::UserManager::Get()->GetUsers();
  int public_session_user_index = FindPublicSession(users);
  if ((!show_users && public_session_user_index == -1) ||
      !HasNonDeviceLocalAccounts(users)) {
    if (!SetDeviceWallpaperIfApplicable(user_manager::SignInAccountId()))
      SetDefaultWallpaperDelayed(user_manager::SignInAccountId());
    return;
  }

  if (!disable_boot_animation) {
    int index = public_session_user_index != -1 ? public_session_user_index : 0;
    SetUserWallpaperDelayed(users[index]->GetAccountId());
  }
}
