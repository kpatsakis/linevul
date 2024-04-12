void TranslateInfoBarDelegate::ToggleSiteBlacklist() {
  if (ui_delegate_.IsSiteBlacklisted()) {
    ui_delegate_.SetSiteBlacklist(false);
  } else {
    ui_delegate_.SetSiteBlacklist(true);
    infobar()->RemoveSelf();
  }
}
