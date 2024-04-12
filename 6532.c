    UserCloudPolicyManagerFactoryChromeOS::GetForProfile(
        Profile* profile) {
  return GetInstance()->GetManagerForProfile(profile);
}
