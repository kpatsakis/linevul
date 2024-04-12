void ExtensionService::AddExtension(const Extension* extension) {
  scoped_refptr<const Extension> scoped_extension(extension);

  if (!extensions_enabled() &&
      !extension->is_theme() &&
      extension->location() != Extension::COMPONENT &&
      !Extension::IsExternalLocation(extension->location()))
    return;

  SetBeingUpgraded(extension, false);

  unloaded_extension_paths_.erase(extension->id());

  UntrackTerminatedExtension(extension->id());

  if (disabled_extension_paths_.erase(extension->id()) > 0)
    EnableExtension(extension->id());

  DisableIfPrivilegeIncrease(extension);

  Extension::State state = extension_prefs_->GetExtensionState(extension->id());
  if (state == Extension::DISABLED) {
    disabled_extensions_.push_back(scoped_extension);
    NotificationService::current()->Notify(
        NotificationType::EXTENSION_UPDATE_DISABLED,
        Source<Profile>(profile_),
        Details<const Extension>(extension));
    return;
  }

  CHECK(state == Extension::ENABLED);
  extensions_.push_back(scoped_extension);
  NotifyExtensionLoaded(extension);
}
