void WallpaperManager::RemoveUserWallpaperInfo(const AccountId& account_id) {
  if (wallpaper_cache_.find(account_id) != wallpaper_cache_.end())
    wallpaper_cache_.erase(account_id);

  PrefService* prefs = g_browser_process->local_state();
  if (!prefs)
    return;
  WallpaperInfo info;
  GetUserWallpaperInfo(account_id, &info);
  DictionaryPrefUpdate prefs_wallpapers_info_update(
      prefs, wallpaper::kUsersWallpaperInfo);
  prefs_wallpapers_info_update->RemoveWithoutPathExpansion(
      account_id.GetUserEmail(), NULL);
  DictionaryPrefUpdate wallpaper_colors_update(prefs,
                                               ash::prefs::kWallpaperColors);
  wallpaper_colors_update->RemoveWithoutPathExpansion(info.location, nullptr);
  DeleteUserWallpapers(account_id, info.location);
}
