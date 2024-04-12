bool WallpaperManagerBase::TestApi::GetWallpaperFromCache(
    const AccountId& account_id,
    gfx::ImageSkia* image) {
  return wallpaper_manager_->GetWallpaperFromCache(account_id, image);
}
