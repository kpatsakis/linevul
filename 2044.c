int ExtensionInstallPrompt::Prompt::GetDialogButtons() const {
  if (type_ == POST_INSTALL_PERMISSIONS_PROMPT && ShouldDisplayRevokeButton()) {
    return kButtons[type_] | ui::DIALOG_BUTTON_OK;
  }

  return kButtons[type_];
}
