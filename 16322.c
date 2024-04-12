void BrowserCommandController::UpdateSharedCommandsForIncognitoAvailability(
    CommandUpdater* command_updater,
    Profile* profile) {
  const bool guest_session = profile->IsGuestSession();
  IncognitoModePrefs::Availability incognito_availability =
      IncognitoModePrefs::GetAvailability(profile->GetPrefs());
  command_updater->UpdateCommandEnabled(
      IDC_NEW_WINDOW,
      incognito_availability != IncognitoModePrefs::FORCED);
  command_updater->UpdateCommandEnabled(
      IDC_NEW_INCOGNITO_WINDOW,
      incognito_availability != IncognitoModePrefs::DISABLED && !guest_session);

  const bool forced_incognito =
      incognito_availability == IncognitoModePrefs::FORCED ||
      guest_session;  // Guest always runs in Incognito mode.
  command_updater->UpdateCommandEnabled(
      IDC_SHOW_BOOKMARK_MANAGER,
      browser_defaults::bookmarks_enabled && !forced_incognito);
  extensions::ExtensionService* extension_service =
      extensions::ExtensionSystem::Get(profile)->extension_service();
  const bool enable_extensions =
      extension_service && extension_service->extensions_enabled();

  command_updater->UpdateCommandEnabled(IDC_MANAGE_EXTENSIONS,
                                        enable_extensions && !forced_incognito);

  command_updater->UpdateCommandEnabled(IDC_IMPORT_SETTINGS, !forced_incognito);
  command_updater->UpdateCommandEnabled(IDC_OPTIONS,
                                        !forced_incognito || guest_session);
  command_updater->UpdateCommandEnabled(IDC_SHOW_SIGNIN, !forced_incognito);
}
