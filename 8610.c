  base::string16 GetSoundSettingString(ContentSetting setting) {
    return PageInfoUI::PermissionActionToUIString(
        profile(), CONTENT_SETTINGS_TYPE_SOUND, setting, default_setting_,
        content_settings::SettingSource::SETTING_SOURCE_USER);
  }
