bool ExtensionAppItem::NeedsOverlay() const {
#if defined(OS_CHROMEOS)
  return false;
#endif

  extensions::LaunchType launch_type =
      GetExtension()
          ? extensions::GetLaunchType(extensions::ExtensionPrefs::Get(profile_),
                                      GetExtension())
          : extensions::LAUNCH_TYPE_WINDOW;

  return !is_platform_app_ && extension_id_ != extension_misc::kChromeAppId &&
         (!extensions::util::IsNewBookmarkAppsEnabled() ||
          launch_type != extensions::LAUNCH_TYPE_WINDOW);
}
