  void SetHostContentSetting(WebContents* contents, ContentSetting setting) {
    HostContentSettingsMapFactory::GetForProfile(
        Profile::FromBrowserContext(contents->GetBrowserContext()))
        ->SetContentSettingDefaultScope(
            contents->GetURL(), GURL(),
            CONTENT_SETTINGS_TYPE_AUTOMATIC_DOWNLOADS, std::string(), setting);
  }
