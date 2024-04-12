  explicit TestObserver(WallpaperManager* wallpaper_manager)
      : update_wallpaper_count_(0), wallpaper_manager_(wallpaper_manager) {
    DCHECK(wallpaper_manager_);
    wallpaper_manager_->AddObserver(this);
  }
