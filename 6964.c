void WebsiteSettingsPopupView::TabSelectedAt(int index) {
  switch (index) {
    case TAB_ID_PERMISSIONS:
      presenter_->RecordWebsiteSettingsAction(
          WebsiteSettings::WEBSITE_SETTINGS_PERMISSIONS_TAB_SELECTED);
      break;
    case TAB_ID_CONNECTION:
      if (presenter_) {
        presenter_->RecordWebsiteSettingsAction(
            WebsiteSettings::WEBSITE_SETTINGS_CONNECTION_TAB_SELECTED);
      }
      break;
    default:
      NOTREACHED();
  }
  tabbed_pane_->GetSelectedTab()->Layout();
  SizeToContents();
}
