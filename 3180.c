void UnlockProfileAndHideLoginUI(const base::FilePath profile_path,
                                 InlineLoginHandlerImpl* handler) {
  if (!profile_path.empty()) {
    ProfileManager* profile_manager = g_browser_process->profile_manager();
    if (profile_manager) {
      ProfileAttributesEntry* entry;
      if (profile_manager->GetProfileAttributesStorage()
              .GetProfileAttributesWithPath(profile_path, &entry)) {
        entry->SetIsSigninRequired(false);
      }
    }
  }
  if (handler)
    handler->CloseDialogFromJavascript();

  UserManager::Hide();
}
