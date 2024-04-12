    ExtensionInstallPrompt::GetLocalizedExtensionForDisplay(
    const base::DictionaryValue* manifest,
    int flags,
    const std::string& id,
    const std::string& localized_name,
    const std::string& localized_description,
    std::string* error) {
  scoped_ptr<base::DictionaryValue> localized_manifest;
  if (!localized_name.empty() || !localized_description.empty()) {
    localized_manifest.reset(manifest->DeepCopy());
    if (!localized_name.empty()) {
      localized_manifest->SetString(extensions::manifest_keys::kName,
                                    localized_name);
    }
    if (!localized_description.empty()) {
      localized_manifest->SetString(extensions::manifest_keys::kDescription,
                                    localized_description);
    }
  }

  return Extension::Create(
      base::FilePath(),
      Manifest::INTERNAL,
      localized_manifest.get() ? *localized_manifest.get() : *manifest,
      flags,
      id,
      error);
}
