views::View* WebsiteSettingsPopupView::CreateConnectionTab() {
  views::View* pane = new views::View();
  pane->SetLayoutManager(
      new views::BoxLayout(views::BoxLayout::kVertical, 0, 0, 1));

  identity_info_content_ = new views::View();
  pane->AddChildView(identity_info_content_);

  pane->AddChildView(new views::Separator(views::Separator::HORIZONTAL));
  connection_info_content_ = new views::View();
  pane->AddChildView(connection_info_content_);

  pane->AddChildView(new views::Separator(views::Separator::HORIZONTAL));
  help_center_link_ = new views::Link(
      l10n_util::GetStringUTF16(IDS_PAGE_INFO_HELP_CENTER_LINK));
  help_center_link_->set_listener(this);
  help_center_content_ = new views::View();
  views::View* link_section =
      CreateSection(base::string16(),
                    help_center_content_,
                    help_center_link_);
  link_section->AddChildView(help_center_link_);
  pane->AddChildView(link_section);
  return pane;
}
