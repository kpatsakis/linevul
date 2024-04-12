void ExtensionInstallUI::OnInstallFailure(const string16& error) {
  DCHECK(ui_loop_ == MessageLoop::current());

  Browser* browser = BrowserList::GetLastActiveWithProfile(profile_);
  if (disable_failure_ui_for_tests)
    return;
  browser::ShowErrorBox(
      browser ? browser->window()->GetNativeHandle() : NULL,
      l10n_util::GetStringUTF16(IDS_EXTENSION_INSTALL_FAILURE_TITLE),
      error);
}
