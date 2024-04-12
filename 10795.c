InstallationState GetAppLauncherInstallationState() {
  if (IsAppLauncherEnabledAtLevel(SYSTEM_LEVEL_INSTALLATION))
    return INSTALLED_AT_SYSTEM_LEVEL;

  if (IsAppLauncherEnabledAtLevel(USER_LEVEL_INSTALLATION))
    return INSTALLED_AT_USER_LEVEL;

  return NOT_INSTALLED;
}
