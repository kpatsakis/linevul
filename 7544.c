ContentSetting GetEffectiveSetting(Profile* profile,
                                   ContentSettingsType type,
                                   ContentSetting setting,
                                   ContentSetting default_setting) {
  ContentSetting effective_setting = setting;
  if (effective_setting == CONTENT_SETTING_DEFAULT)
    effective_setting = default_setting;

  if (effective_setting == CONTENT_SETTING_DETECT_IMPORTANT_CONTENT)
    effective_setting = CONTENT_SETTING_ASK;

  return effective_setting;
}
