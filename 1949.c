ExtensionSettingsHandler::GetExtensionUninstallDialog() {
  if (!extension_uninstall_dialog_.get()) {
    extension_uninstall_dialog_.reset(
        ExtensionUninstallDialog::Create(Profile::FromWebUI(web_ui()), this));
  }
  return extension_uninstall_dialog_.get();
}
