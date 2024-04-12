base::string16 PageInfoUI::PermissionActionToUIString(
    Profile* profile,
    ContentSettingsType type,
    ContentSetting setting,
    ContentSetting default_setting,
    content_settings::SettingSource source) {
  ContentSetting effective_setting =
      GetEffectiveSetting(profile, type, setting, default_setting);
  const int* button_text_ids = NULL;
  switch (source) {
    case content_settings::SETTING_SOURCE_USER:
      if (setting == CONTENT_SETTING_DEFAULT) {
#if !defined(OS_ANDROID)
        if (type == CONTENT_SETTINGS_TYPE_SOUND &&
            base::FeatureList::IsEnabled(media::kAutoplayWhitelistSettings)) {
          if (profile->GetPrefs()->GetBoolean(prefs::kBlockAutoplayEnabled) &&
              effective_setting == ContentSetting::CONTENT_SETTING_ALLOW) {
            return l10n_util::GetStringUTF16(
                IDS_PAGE_INFO_BUTTON_TEXT_AUTOMATIC_BY_DEFAULT);
          }

          button_text_ids = kSoundPermissionButtonTextIDDefaultSetting;
          break;
        }
#endif

        button_text_ids = kPermissionButtonTextIDDefaultSetting;
        break;
      }
      FALLTHROUGH;
    case content_settings::SETTING_SOURCE_POLICY:
    case content_settings::SETTING_SOURCE_EXTENSION:
#if !defined(OS_ANDROID)
      if (type == CONTENT_SETTINGS_TYPE_SOUND &&
          base::FeatureList::IsEnabled(media::kAutoplayWhitelistSettings)) {
        button_text_ids = kSoundPermissionButtonTextIDUserManaged;
        break;
      }
#endif

      button_text_ids = kPermissionButtonTextIDUserManaged;
      break;
    case content_settings::SETTING_SOURCE_WHITELIST:
    case content_settings::SETTING_SOURCE_NONE:
    default:
      NOTREACHED();
      return base::string16();
  }
  int button_text_id = button_text_ids[effective_setting];
  DCHECK_NE(button_text_id, kInvalidResourceID);
  return l10n_util::GetStringUTF16(button_text_id);
}
