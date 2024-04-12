void Extension::GetBasicInfo(bool enabled,
                             DictionaryValue* info) const {
  info->SetString(info_keys::kIdKey, id());
  info->SetString(info_keys::kNameKey, name());
  info->SetBoolean(info_keys::kEnabledKey, enabled);
  info->SetBoolean(info_keys::kOfflineEnabledKey, offline_enabled());
  info->SetString(info_keys::kVersionKey, VersionString());
  info->SetString(info_keys::kDescriptionKey, description());
  info->SetString(info_keys::kOptionsUrlKey,
                  ManifestURL::GetOptionsPage(this).possibly_invalid_spec());
  info->SetString(info_keys::kHomepageUrlKey,
                  ManifestURL::GetHomepageURL(this).possibly_invalid_spec());
  info->SetString(info_keys::kDetailsUrlKey,
                  ManifestURL::GetDetailsURL(this).possibly_invalid_spec());
  info->SetBoolean(info_keys::kPackagedAppKey, is_platform_app());
}
