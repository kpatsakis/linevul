void ExtensionSettingsHandler::ExtensionUninstallAccepted() {
  DCHECK(!extension_id_prompting_.empty());

  bool was_terminated = false;

  const Extension* extension =
      extension_service_->GetExtensionById(extension_id_prompting_, true);
  if (!extension) {
    extension = extension_service_->GetTerminatedExtension(
        extension_id_prompting_);
    was_terminated = true;
  }
  if (!extension)
    return;

  extension_service_->UninstallExtension(extension_id_prompting_,
                                         false,  // External uninstall.
                                         NULL);  // Error.
  extension_id_prompting_ = "";

  if (was_terminated)
    HandleRequestExtensionsData(NULL);
}
