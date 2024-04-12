void ExtensionSettingsHandler::HandleEnableMessage(const ListValue* args) {
  CHECK_EQ(2U, args->GetSize());
  std::string extension_id, enable_str;
  CHECK(args->GetString(0, &extension_id));
  CHECK(args->GetString(1, &enable_str));

  const Extension* extension =
      extension_service_->GetExtensionById(extension_id, true);
  if (!Extension::UserMayDisable(extension->location())) {
    LOG(ERROR) << "Attempt to enable an extension that is non-usermanagable was"
               << "made. Extension id: " << extension->id();
    return;
  }

  if (enable_str == "true") {
    ExtensionPrefs* prefs = extension_service_->extension_prefs();
    if (prefs->DidExtensionEscalatePermissions(extension_id)) {
      ShowExtensionDisabledDialog(extension_service_,
                                  Profile::FromWebUI(web_ui()), extension);
    } else {
      extension_service_->EnableExtension(extension_id);
    }
  } else {
    extension_service_->DisableExtension(extension_id);
  }
}
