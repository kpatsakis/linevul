void Browser::OpenHelpTab() {
  GURL help_url(kHelpContentUrl);
  GURL localized_help_url = google_util::AppendGoogleLocaleParam(help_url);
  AddSelectedTabWithURL(localized_help_url, PageTransition::AUTO_BOOKMARK);
}
