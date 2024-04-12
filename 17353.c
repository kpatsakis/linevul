void UserCloudPolicyManagerFactoryChromeOS::BrowserContextDestroyed(
    content::BrowserContext* context) {
  Profile* profile = static_cast<Profile*>(context);
  managers_.erase(profile);
  BrowserContextKeyedBaseFactory::BrowserContextDestroyed(context);
}
