void ExtensionInstallPrompt::ConfirmWebstoreInstall(
    Delegate* delegate,
    const Extension* extension,
    const SkBitmap* icon,
    const ShowDialogCallback& show_dialog_callback) {
  extension_ = extension;
  SetIcon(icon);
  ConfirmInstall(delegate, extension, show_dialog_callback);
}
