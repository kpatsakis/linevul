  base::string16 GetDefaultSoundSettingString() {
    return PageInfoUI::PermissionActionToUIString(
        profile(), CONTENT_SETTINGS_TYPE_SOUND, CONTENT_SETTING_DEFAULT,
        default_setting_, content_settings::SettingSource::SETTING_SOURCE_USER);
  }
