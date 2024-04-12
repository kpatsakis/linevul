CrostiniUpgrader::CrostiniUpgrader(Profile* profile)
    : profile_(profile), container_id_("", "") {
  CrostiniManager::GetForProfile(profile_)->AddUpgradeContainerProgressObserver(
      this);
}
