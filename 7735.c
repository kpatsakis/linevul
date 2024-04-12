views::View* WebsiteSettingsPopupView::CreatePermissionsTab() {
  views::View* pane = new views::View();
  pane->SetLayoutManager(
      new views::BoxLayout(views::BoxLayout::kVertical, 0, 0, 1));

  cookie_dialog_link_ = new views::Link(
      l10n_util::GetStringUTF16(IDS_WEBSITE_SETTINGS_SHOW_SITE_DATA));
  cookie_dialog_link_->set_listener(this);
  site_data_content_ = new views::View();
  views::View* site_data_section =
      CreateSection(l10n_util::GetStringUTF16(
                        IDS_WEBSITE_SETTINGS_TITLE_SITE_DATA),
                    site_data_content_,
                    cookie_dialog_link_);
  pane->AddChildView(site_data_section);

  return pane;
}
