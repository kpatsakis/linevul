void ExtensionInstallPrompt::LoadImageIfNeeded() {
  if (!icon_.empty() || !profile_) {
    ShowConfirmation();
    return;
  }

  extensions::ExtensionResource image = extensions::IconsInfo::GetIconResource(
      extension_,
      extension_misc::EXTENSION_ICON_LARGE,
      ExtensionIconSet::MATCH_BIGGER);

  extensions::ImageLoader* loader = extensions::ImageLoader::Get(profile_);

  std::vector<extensions::ImageLoader::ImageRepresentation> images_list;
  images_list.push_back(extensions::ImageLoader::ImageRepresentation(
      image,
      extensions::ImageLoader::ImageRepresentation::NEVER_RESIZE,
      gfx::Size(),
      ui::SCALE_FACTOR_100P));
  loader->LoadImagesAsync(
      extension_,
      images_list,
      base::Bind(&ExtensionInstallPrompt::OnImageLoaded, AsWeakPtr()));
}
