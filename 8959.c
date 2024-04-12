AppLauncherHandler::AppLauncherHandler(ExtensionService* extension_service)
    : extension_service_(extension_service),
      ignore_changes_(false),
      attempted_bookmark_app_install_(false),
      has_loaded_apps_(false) {
  if (IsAppLauncherEnabled())
    RecordAppLauncherPromoHistogram(apps::APP_LAUNCHER_PROMO_ALREADY_INSTALLED);
  else if (ShouldShowAppLauncherPromo())
    RecordAppLauncherPromoHistogram(apps::APP_LAUNCHER_PROMO_SHOWN);
}
