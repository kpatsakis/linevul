void WebsiteSettingsPopupView::SetPermissionInfo(
    const PermissionInfoList& permission_info_list) {
  permissions_content_ = new views::View();
  views::GridLayout* layout = new views::GridLayout(permissions_content_);
  permissions_content_->SetLayoutManager(layout);

  base::string16 headline =
      permission_info_list.empty()
          ? base::string16()
          : l10n_util::GetStringUTF16(
                IDS_WEBSITE_SETTINGS_TITLE_SITE_PERMISSIONS);
  views::View* permissions_section =
      CreateSection(headline, permissions_content_, nullptr);
  permissions_tab_->AddChildView(permissions_section);

  const int content_column = 0;
  views::ColumnSet* column_set = layout->AddColumnSet(content_column);
  column_set->AddColumn(views::GridLayout::FILL,
                        views::GridLayout::FILL,
                        1,
                        views::GridLayout::USE_PREF,
                        0,
                        0);
  for (PermissionInfoList::const_iterator permission =
           permission_info_list.begin();
       permission != permission_info_list.end();
       ++permission) {
    layout->StartRow(1, content_column);
    PermissionSelectorView* selector = new PermissionSelectorView(
        web_contents_ ? web_contents_->GetURL() : GURL::EmptyGURL(),
        *permission);
    selector->AddObserver(this);
    layout->AddView(selector,
                    1,
                    1,
                    views::GridLayout::LEADING,
                    views::GridLayout::CENTER);
    layout->AddPaddingRow(1, kPermissionsSectionRowSpacing);
  }

  layout->Layout(permissions_content_);

  site_settings_link_ = new views::Link(
      l10n_util::GetStringUTF16(IDS_PAGE_INFO_SITE_SETTINGS_LINK));
  site_settings_link_->set_listener(this);
  views::View* link_section = new views::View();
  const int kLinkMarginTop = 4;
  link_section->SetLayoutManager(
      new views::BoxLayout(views::BoxLayout::kHorizontal,
                           kConnectionSectionPaddingLeft, kLinkMarginTop, 0));
  link_section->AddChildView(site_settings_link_);
  permissions_tab_->AddChildView(link_section);

  SizeToContents();
}
