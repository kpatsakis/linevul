void WallpaperManager::EnsureLoggedInUserWallpaperLoaded() {
  WallpaperInfo info;
  if (GetLoggedInUserWallpaperInfo(&info)) {
    UMA_HISTOGRAM_ENUMERATION("Ash.Wallpaper.Type", info.type,
                              wallpaper::WALLPAPER_TYPE_COUNT);
    RecordWallpaperAppType();
    if (info == current_user_wallpaper_info_)
      return;
  }
  SetUserWallpaperNow(
      user_manager::UserManager::Get()->GetActiveUser()->GetAccountId());
}
