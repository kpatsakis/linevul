void WallpaperManager::AddObservers() {
  show_user_name_on_signin_subscription_ =
      CrosSettings::Get()->AddSettingsObserver(
          kAccountsPrefShowUserNamesOnSignIn,
          base::Bind(&WallpaperManager::InitializeRegisteredDeviceWallpaper,
                     weak_factory_.GetWeakPtr()));
  device_wallpaper_image_subscription_ =
      CrosSettings::Get()->AddSettingsObserver(
          kDeviceWallpaperImage,
          base::Bind(&WallpaperManager::OnDeviceWallpaperPolicyChanged,
                     weak_factory_.GetWeakPtr()));
}
