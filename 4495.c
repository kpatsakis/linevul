void WallpaperManagerBase::ResizeCustomizedDefaultWallpaper(
    std::unique_ptr<gfx::ImageSkia> image,
    const CustomizedWallpaperRescaledFiles* rescaled_files,
    bool* success,
    gfx::ImageSkia* small_wallpaper_image,
    gfx::ImageSkia* large_wallpaper_image) {
  *success = true;

  *success &= ResizeAndSaveWallpaper(
      *image, rescaled_files->path_rescaled_small(), WALLPAPER_LAYOUT_STRETCH,
      kSmallWallpaperMaxWidth, kSmallWallpaperMaxHeight, small_wallpaper_image);

  *success &= ResizeAndSaveWallpaper(
      *image, rescaled_files->path_rescaled_large(), WALLPAPER_LAYOUT_STRETCH,
      kLargeWallpaperMaxWidth, kLargeWallpaperMaxHeight, large_wallpaper_image);
}
