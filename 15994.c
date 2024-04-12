void Browser::OpenThemeGalleryTabAndActivate() {
  AddSelectedTabWithURL(GURL(l10n_util::GetStringUTF8(IDS_THEMES_GALLERY_URL)),
                        PageTransition::LINK);
}
