void ExtensionInstallPrompt::ConfirmInstall(
    Delegate* delegate,
    const Extension* extension,
    const ShowDialogCallback& show_dialog_callback) {
  DCHECK(ui_loop_ == base::MessageLoop::current());
  extension_ = extension;
  delegate_ = delegate;
  prompt_ = new Prompt(INSTALL_PROMPT);
  show_dialog_callback_ = show_dialog_callback;

  if (extension->is_theme()) {
    if (extension->from_webstore() ||
        extensions::FeatureSwitch::easy_off_store_install()->IsEnabled()) {
      delegate->InstallUIProceed();
      return;
    }
  }

  LoadImageIfNeeded();
}
