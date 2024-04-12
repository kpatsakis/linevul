void BrowserCommandController::OnStateChanged() {
  DCHECK(ProfileSyncServiceFactory::GetInstance()->HasProfileSyncService(
      profile()));
  if (!window())
    return;
  const bool show_main_ui = IsShowingMainUI(window()->IsFullscreen());
  command_updater_.UpdateCommandEnabled(IDC_SHOW_SYNC_SETUP,
      show_main_ui && profile()->GetOriginalProfile()->IsSyncAccessible());
}
