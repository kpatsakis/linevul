  explicit FlashContentSettingsChangeWaiter(Profile* profile)
      : profile_(profile) {
    HostContentSettingsMapFactory::GetForProfile(profile)->AddObserver(this);
  }
