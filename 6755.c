bool BrowserWindowGtk::UsingCustomPopupFrame() const {
  GtkThemeService* theme_provider = GtkThemeService::GetFrom(
      browser()->profile());
  return !theme_provider->UsingNativeTheme() && browser()->is_type_popup();
}
