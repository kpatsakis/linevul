void SupervisedUserService::UpdateApprovedExtensions() {
  const base::DictionaryValue* dict = profile_->GetPrefs()->GetDictionary(
      prefs::kSupervisedUserApprovedExtensions);
  std::set<std::string> extensions_to_be_checked;
  for (const auto& extension : approved_extensions_map_)
    extensions_to_be_checked.insert(extension.first);

  approved_extensions_map_.clear();

  for (base::DictionaryValue::Iterator it(*dict); !it.IsAtEnd(); it.Advance()) {
    std::string version_str;
    bool result = it.value().GetAsString(&version_str);
    DCHECK(result);
    base::Version version(version_str);
    if (version.IsValid()) {
      approved_extensions_map_[it.key()] = version;
      extensions_to_be_checked.insert(it.key());
    } else {
      LOG(WARNING) << "Invalid version number " << version_str;
    }
  }

  for (const auto& extension_id : extensions_to_be_checked) {
    ChangeExtensionStateIfNecessary(extension_id);
  }
}
