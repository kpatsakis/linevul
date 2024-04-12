const gfx::ImageSkia& Extension::GetDefaultIcon(bool is_app) {
  int id = is_app ? IDR_APP_DEFAULT_ICON : IDR_EXTENSION_DEFAULT_ICON;
  return *ResourceBundle::GetSharedInstance().GetImageSkiaNamed(id);
}
