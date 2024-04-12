void ExtensionServiceBackend::ReportExtensionLoadError(
    const FilePath& extension_path, const std::string &error) {
  CHECK(BrowserThread::CurrentlyOn(BrowserThread::UI));
  if (frontend_.get())
    frontend_->ReportExtensionLoadError(
        extension_path, error, NotificationType::EXTENSION_INSTALL_ERROR,
         true /* alert_on_error */);
 }
